/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** RoomInstance
*/

#pragma once

#include <boost/process.hpp>
#include <boost/thread.hpp>
#include "Communicator/Client.hpp"

namespace serverData
{
    /// The class declared in the Server.hpp header file
    class Server;

    /// @brief A class that represents a room instance.
    class RoomInstance {
      public:
        /// @brief All the possible state of a room
        enum RoomState { UNDEFINED, LOBBY, IN_GAME, ENDED };

        /// @brief It creates a new room instance
        /// @param id The id of the room.
        /// @param name The name of the room.
        /// @param address The address of the server.
        /// @param port the port on which the room will listen to
        RoomInstance(Server *server, unsigned short id, std::string name, std::string address, unsigned short port);

        /// @brief The destructor for the RoomInstance class
        /// It waits that the process is stoped
        ~RoomInstance();

        /// @brief It returns the Id of the room.
        /// @return The Id of the room
        inline unsigned short getId() const { return _id; }

        /// @brief It returns the name of the room.
        /// @return The name of the room
        inline std::string getName() const { return _name; }

        /// @brief It returns the network informations of the client
        /// @return The network informations.
        inline communicator_lib::Client getNetworkInfos() const { return _networkInformations; }

        /// @brief It returns a reference to the input stream of the process
        /// @return The input stream of the process
        inline boost::process::opstream &getInputStream() { return *_input; }

        /// @brief It returns a reference to the output stream of the process
        /// @return The output stream of the process
        inline boost::process::ipstream &getOutputStream() { return *_output; }

        /// @brief If the child process is running, terminate it.
        inline void terminate() { _child->terminate(); }

        /// @brief It waits for the process to finish
        inline void wait() { _child->wait(); }

      private:
        /// @brief Id of the room
        unsigned short _id;

        /// @brief Name of the room
        std::string _name;

        /// @brief Current state of the room
        RoomState _state;

        /// @brief Number of remaining places inside the room
        unsigned short _remainingPlaces;

        /// @brief Network informations of the room
        communicator_lib::Client _networkInformations;

        /// @brief The input stream of the process
        boost::process::opstream *_input;

        /// @brief The output stream of the process
        boost::process::ipstream *_output;

        /// @brief The child process which is running the room
        boost::process::child *_child;

        /// @brief The thread used to read and manage interprocess communications
        boost::thread _inputHandler;

        /// @brief Check if the Room instance has to be finished
        bool _terminated;

        /// @brief The function used by _inputHandler to manage the interproccess communications
        /// It reads the output of the game process and manages the responses
        /// @param server The server that created the room.
        void _manageInterprocessCommunication(Server *server);

        /// @brief It takes a line, checks if it's a status response, and if it is, it sets
        /// the room's state to the state in the response
        /// @param line The line of text that was received from the server.
        void _manageStatusResponse(std::string line);

        /// @brief It takes a line as a parameter, and if it's a seats response, and if it is, it sets
        /// the room's remaining places to the response
        /// @param line The line received from the server
        void _manageSeatsResponse(std::string line);

        /// @brief It manages the response of the server to the stop command
        /// @param line the line received from the client
        /// @param server The server that the room is running on.
        void _manageStopResponse(std::string line, Server *server);

        /// @brief If the room tells that its game is ended, stop the room
        /// @param line The line that was received from the server.
        void _manageEndGameRoom(std::string line);

        /// @brief It asks the room to stop
        void _stop();
    };

    /// @brief Overload of the == operator to compare two rooms
    /// @param left param of the comparison
    /// @param right param of the comparison
    /// @return true If the two rooms have the same id
    /// @return false If the two rooms have different id
    inline bool operator==(const RoomInstance &left, const RoomInstance &right)
    {
        return (left.getId() == right.getId());
    }

    /// @brief Overload of the == operator to compare rooms with her id
    /// @param left param of the comparison
    /// @param right param of the comparison
    /// @return true If the two rooms have the same id
    /// @return false If the two rooms have different id
    inline bool operator==(const RoomInstance &left, const unsigned short &right) { return (left.getId() == right); }

    /// @brief Overload of the == operator to compare rooms with her name
    /// @param left param of the comparison
    /// @param right param of the comparison
    /// @return true If the room have the good name
    /// @return false If the room haven't the good name
    inline bool operator==(const RoomInstance &left, const std::string &right) { return (left.getName() == right); }

} // namespace serverData
