/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** Client
*/

/// @file Client/ClientRoom.hpp

#ifndef CLIENT_ROOM_HPP_
#define CLIENT_ROOM_HPP_

#include <memory>
#include "Communicator/Client.hpp"
#include "Communicator/Communicator.hpp"
#include "GraphicECS/SFML/Resources/GraphicsTextureResource.hpp"
#include "Transisthor/Transisthor.hpp"
#include "World/World.hpp"

using namespace communicator_lib;
using namespace ecs;
using namespace transisthor_lib;

namespace client_data
{
    /// @brief Place where the game run (Like a lobby). Hold all libraries instance,
    class ClientRoom {
      public:
        /// @brief All the possible state of a client
        enum ClientState { UNDEFINED, LOBBY, IN_GAME, ENDED };

        /// @brief Construct a new ClientRoom with default value
        ClientRoom();

        /// @brief Construct a new ClientRoom
        /// @param address The ClientRoom address
        /// @param port ClientRoom port
        /// @param serverAddress server address
        /// @param serverPort room port
        ClientRoom(std::string address, unsigned short port, std::string serverAddress, unsigned short serverPort);

        /// @brief Destroy the ClientRoom object
        ~ClientRoom() = default;

        /// @brief Launch the lobby global loop for a multiplayer game
        /// @param pseudo The pseudo of the user
        /// @param password The password of the user
        void startLobbyLoop(const std::string &pseudo, const std::string &password);

        /// @brief This function start the game for the player to choose
        /// if the player is in Solo or Multiplayer mod
        int startGame();

      private:
        /// @brief Get call back handler for a solo game
        void _signalSoloCallbackHandler(int signum);

        /// @brief Launch the lobby global loop for a solo game
        void _startSoloLoop();

        /// @brief Init all shared resources of the world.
        void _initSharedResources();

        /// @brief This function allows to get name and password of the player for the server
        int _choosePlayerInfosForServer();

        /// @brief This function create all entities needed for a solo game
        void _initSoloData();

        /// @brief Init all systems of the world.
        /// @param isSolo Tell if the game is in solo or multiplayer MODE
        void _initSystems(bool isSolo);

        /// @brief Init some entities only created by the client.
        void _initEntities();

        /// @brief Handle a disconnection request. Identify the player and add to it a disconnection component
        void _holdADisconnectionRequest();

        /// @brief Handle a new chat request. Display it on the screen.
        /// @param chatRequest actual message data
        void _holdAChatRequest(CommunicatorMessage chatRequest);

        /// @brief Send to the server the disconnection signal
        void _disconectionProcess();

        /// @brief Init all the Sprites in the GameTextureResource
        void _initSpritesForEntities();

        /// @brief Init all the Entities for the parallax (background)
        void _initBackgroundEntities();

        /// @brief Init all the Buttons and the linked actions
        void _initButtons();

        /// @brief Init all the Writable and the linked actions
        void _initWritable();

        /// @brief Ask the user to enter his Pseudonyme and password
        void _getClientPseudoAndPassword();

        /// @brief Hold a room connection process
        void _connectToARoom();

        /// @brief Init all the sprites needed for the player
        /// @param spritesList texture's map holding the texture and the corresponding key
        void _initSpritesForPlayer(graphicECS::SFML::Resources::GraphicsTextureResource &spritesList);

        /// @brief Init all the sprites needed for the projectiles
        /// @param spritesList texture's map holding the texture and the corresponding key
        void _initSpritesForProjectiles(graphicECS::SFML::Resources::GraphicsTextureResource &spritesList);

        /// @brief Init all the sprites needed for the backgrounds
        /// @param spritesList texture's map holding the texture and the corresponding key
        void _initSpritesForBackgrounds(graphicECS::SFML::Resources::GraphicsTextureResource &spritesList);

        /// @brief Init all the sprites needed for the Writable object
        /// @param spritesList texture's map holding the texture and the corresponding key
        void _initSpritesForWritable(graphicECS::SFML::Resources::GraphicsTextureResource &spritesList);

        /// @brief Network informations of the room.
        Client _networkInformations;

        /// @brief Network informations of the server
        Client _serverEndpoint;

        /// @brief Current state of the client
        ClientState _state;

        /// @brief Client pseudoname
        std::string _pseudo;

        /// @brief Client password
        std::string _password;

        /// @brief Instance of the communicator library
        std::shared_ptr<Communicator> _communicatorInstance;

        /// @brief Instance of the transisthor library
        std::shared_ptr<Transisthor> _transisthorInstance;

        /// @brief Instance of the ECS library
        std::shared_ptr<World> _worldInstance;

        /// @brief Init the Ressources and Systems of the ECS
        /// @param isSolo True if the player choose to play in solo. False if he want to play in multiplayer
        void _initEcsGameData(bool isSolo);

        /// @brief Start the connexion protocol and ask the server for a place inside the room
        void _startConnexionProtocol(void);

        /// @brief Answer the reception of a protocol 12
        void protocol12Answer(CommunicatorMessage connexionResponse);

        /// @brief Answer the reception of a protocol 15
        /// @param connectionResponse The received response
        void _protocol15Answer(CommunicatorMessage connectionResponse);
    };
} // namespace client_data

#endif /* !CLIENT_HPP_ */
