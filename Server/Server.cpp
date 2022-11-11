/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** Server
*/

/// @file Server/Server.cpp

#include "Server.hpp"
#include "Error/Error.hpp"

using namespace server_data;
using namespace error_lib;
using namespace communicator_lib;

Server::Server(std::string address, unsigned short port)
{
    _networkInformations = Client(address, port);
    _state = HubState::UNDEFINED;
    _communicatorInstance = std::make_shared<Communicator>(_networkInformations);
    _nextRoomId = 0;
    _databaseApi.createUserTable();
    auto apiAnswer = _databaseApi.selectUsers("UserName = 'admin'");
    if (apiAnswer.empty())
        _databaseApi.addUser("admin", "admin", true, false, false);
}

Server::Server()
{
    _activeRoomList = {};
    _networkInformations = Client();
    _state = HubState::UNDEFINED;
    _communicatorInstance = std::make_shared<Communicator>(_networkInformations);
    _databaseApi.createUserTable();
    auto apiAnswer = _databaseApi.selectUsers("UserName = 'admin'");
    if (apiAnswer.empty())
        _databaseApi.addUser("admin", "admin", true, false, false);
}

unsigned short Server::_getAFreePort(unsigned short actual)
{
    try {
        boost::asio::io_service io_service;
        boost::asio::ip::udp::socket socket(io_service);
        socket.open(boost::asio::ip::udp::v4());
        socket.bind(boost::asio::ip::udp::endpoint(
            boost::asio::ip::address::from_string(_networkInformations.getAddress()), actual));
        return actual;
    } catch (const boost::system::system_error &error) {
        return _getAFreePort(actual + 101);
    }
}

unsigned short Server::createANewRoom(std::string name, short *configs)
{
    std::shared_ptr<RoomInstance> ptr = std::make_shared<RoomInstance>(this, _nextRoomId, name,
        _networkInformations.getAddress(), _getAFreePort(_networkInformations.getPort() + 101), configs);
    _activeRoomList.push_back(ptr);
    _nextRoomId++;
    return (_nextRoomId - 1);
}

void Server::_startConnexionProtocol()
{
    _communicatorInstance.get()->startReceiverListening();
    _state = HubState::HUB;
}

void Server::startHubLoop()
{
    CommunicatorMessage connectionOperation;

    _startConnexionProtocol();
    while (_state != HubState::UNDEFINED && _state != HubState::ENDED) {
        try {
            connectionOperation = _communicatorInstance.get()->getLastMessage();
            if (connectionOperation.message.type == 13)
                _holdADisconnectionRequest(connectionOperation);
            if (connectionOperation.message.type == 14)
                _holdANewConnectionRequest(connectionOperation);
            if (connectionOperation.message.type == 16)
                _holdAJoinRoomRequest(connectionOperation);
            if (connectionOperation.message.type == 17)
                _holdACreateRoomRequest(connectionOperation);
            if (connectionOperation.message.type == 40)
                _holdADatabaseValueRequest(connectionOperation);
            if (connectionOperation.message.type == 42)
                _holdADatabaseSetRequest(connectionOperation);
            if (connectionOperation.message.type == 44)
                _holdAScoreboardRequest(connectionOperation);
        } catch (NetworkError &error) {
        }
    }
    _disconnectionProcess();
}

void Server::_holdADatabaseValueRequest(CommunicatorMessage databaseRequest)
{
    std::vector<std::string> requestContent =
        _communicatorInstance->utilitaryReceiveAskingForDatabaseValue(databaseRequest);
    auto apiAnswer = _databaseApi.selectUsers("UserName = '" + requestContent.at(0) + "'");
    if (apiAnswer.empty()) {
        _communicatorInstance->sendDataToAClient(databaseRequest.message.clientInfo, nullptr, 0, 43);
        return;
    }
    _communicatorInstance->utilitarySendDatabaseValue(
        apiAnswer.at(0)[requestContent.at(1)], databaseRequest.message.clientInfo);
}

void Server::_holdAScoreboardRequest(CommunicatorMessage databaseRequest)
{
    std::string key = _communicatorInstance->utilitaryReceiveScoreboardAsking(databaseRequest);
    std::map<std::string, int> scoreboard;
    std::size_t count = 0;
    auto apiAnswer = _databaseApi.selectUsers("Banned = 0 ORDER BY " + key + " DESC");

    for (auto it : apiAnswer) {
        if (count > 4)
            break;
        scoreboard[it["UserName"]] = std::atoi(it[key].c_str());
        count++;
    }
    _communicatorInstance->utilitarySendALeaderboard(scoreboard, {databaseRequest.message.clientInfo.getId()});
}

void Server::_holdADatabaseSetRequest(CommunicatorMessage databaseRequest)
{
    std::vector<std::string> requestContent = _communicatorInstance->utilitaryReceiveSetDatabaseValue(databaseRequest);
    std::string keyStr = "";

    if (requestContent.at(1) == "1")
        keyStr = "Banned";
    if (requestContent.at(1) == "2")
        keyStr = "Muted";
    if (requestContent.at(1) == "3")
        keyStr = "Moderator";
    if (requestContent.at(1) == "4")
        keyStr = "UserName";
    if (requestContent.at(1) == "5")
        keyStr = "Password";
    _databaseApi.updateUsers(keyStr + " = " + requestContent.at(2), "UserName = '" + requestContent.at(0) + "'");
}

void Server::_disconnectionProcess()
{
    auto clientList = _communicatorInstance.get()->getClientList();

    for (auto it : clientList)
        _communicatorInstance.get()->sendDataToAClient(it, nullptr, 0, 13);
}

void Server::_holdADisconnectionRequest(CommunicatorMessage disconnectionDemand)
{
    _communicatorInstance.get()->sendDataToAClient(disconnectionDemand.message.clientInfo, nullptr, 0, 13);
}

void Server::_holdAJoinRoomRequest(CommunicatorMessage joinDemand)
{
    unsigned short choosenRoom = 0;

    std::memcpy(&choosenRoom, joinDemand.message.data, sizeof(unsigned short));
    for (auto &it : _activeRoomList) {
        if (it->getId() == choosenRoom) {
            _communicatorInstance.get()->kickAClient(joinDemand.message.clientInfo, it->getNetworkInfos());
            return;
        }
    }
    _communicatorInstance.get()->sendDataToAClient(joinDemand.message.clientInfo, nullptr, 0, 11);
}

void Server::_holdACreateRoomRequest(CommunicatorMessage createDemand)
{
    RoomConfiguration room = _communicatorInstance->utilitaryReceiveRoomConfiguration(createDemand);

    for (auto &it : _activeRoomList) {
        if (it->getName() == room.roomName) {
            _communicatorInstance->sendDataToAClient(createDemand.message.clientInfo, nullptr, 0, 11);
            return;
        }
    }

    unsigned short roomId = createANewRoom(room.roomName, room.configs);
    for (auto &it : _activeRoomList) {
        if (it->getId() == roomId) {
            _communicatorInstance->kickAClient(createDemand.message.clientInfo, it->getNetworkInfos());
            return;
        }
    }
}

void Server::_holdANewConnectionRequest(CommunicatorMessage connectionDemand)
{
    unsigned short offset = 0;
    unsigned short passwordSize = 0;
    unsigned short pseudoSize = 0;

    std::memcpy(&pseudoSize, connectionDemand.message.data, sizeof(unsigned short));
    offset += sizeof(unsigned short);
    char *pseudo = (char *)connectionDemand.message.data + offset;
    offset += sizeof(char) * pseudoSize;
    std::memcpy(&passwordSize, (void *)((char *)connectionDemand.message.data + offset), sizeof(unsigned short));
    offset += sizeof(unsigned short);
    char *password = (char *)connectionDemand.message.data + offset;
    offset += sizeof(char) * passwordSize;
    std::string pseudoStr = std::string(pseudoSize, '\0');
    std::string passwordStr = std::string(passwordSize, '\0');

    for (int i = 0; i < pseudoSize; i++)
        pseudoStr[i] += pseudo[i];
    for (int i = 0; i < passwordSize; i++)
        passwordStr[i] = password[i];
    auto apiAnswer = _databaseApi.selectUsers("UserName = '" + pseudoStr + "'");
    if (apiAnswer.empty()) {
        _databaseApi.addUser(pseudoStr, passwordStr, false, false, false);
    } else {
        if (apiAnswer.at(0)["Password"] != passwordStr || apiAnswer.at(0)["Banned"] != "0") {
            _communicatorInstance.get()->sendDataToAClient(connectionDemand.message.clientInfo, nullptr, 0, 11);
            return;
        }
    }
    void *networkData =
        std::malloc(sizeof(unsigned short) + _activeRoomList.size() * (sizeof(unsigned short) * 2 + sizeof(char) * 10));
    offset = 0;
    unsigned short roomListSize = _activeRoomList.size();

    if (networkData == nullptr)
        throw std::logic_error("Malloc failed.");
    std::memcpy(networkData, &roomListSize, sizeof(unsigned short));
    offset += sizeof(unsigned short);
    for (auto &it : _activeRoomList) {
        unsigned short roomId = it->getId();
        std::string roomName = it->getName();
        unsigned short nameSize = roomName.size();

        std::memcpy((void *)((char *)networkData + offset), &roomId, sizeof(unsigned short));
        offset += sizeof(unsigned short);
        std::memcpy((void *)((char *)networkData + offset), &nameSize, sizeof(unsigned short));
        offset += sizeof(unsigned short);
        std::memcpy((void *)((char *)networkData + offset), roomName.c_str(), sizeof(char) * nameSize);
        offset += sizeof(char) * nameSize;
    }
    _communicatorInstance.get()->sendDataToAClient(connectionDemand.message.clientInfo, networkData, offset, 15);
}

void Server::deleteARoom(unsigned short id)
{
    int pos = 0;

    for (auto &it : _activeRoomList) {
        if (it->getId() == id) {
            _activeRoomList.erase(_activeRoomList.begin() + pos);
        }
        pos++;
    }
}
