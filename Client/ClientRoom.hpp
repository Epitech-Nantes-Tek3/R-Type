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
        enum ClientState { UNDEFINED, MAIN_MENU, LOBBY, IN_GAME, ENDED };

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
        void startLobbyLoop(const std::string &pseudo, const std::string &password, bool isSolo);

        /// @brief This function start the game for the player to choose
        /// if the player is in Solo or Multiplayer mod
        int startGame();

      private:
        void _initLobbyMenuButtons();
        /// @brief It sends the pseudo of the client to the server
        void _connectToARoom();

        /// @brief It creates two buttons, one for the lobby and one for exiting the game
        void _initMainMenuButtons();

        /// @brief It creates four entities with a parallax background component, a graphics
        /// rectangle component, a position component, a velocity component, a layer level
        /// component, and a texture name component
        void _initInGameBackgrounds();

        /// @brief It loads the button actions into the button action map
        /// @param isSolo true if it's a solo game, false otherwise
        void _loadButtonActionMap(bool isSolo);

        /// @brief It creates an entity with all the input components and sets the
        /// keyboard and mouse inputs to the entity
        void _initInputsEntity();

        /// @brief It loads all the textures needed for the game
        void _loadTextures();

        /// @brief It updates the ECS data
        /// @param isSolo If true, the client will be the only player in the room.
        void _updateEcsData(bool isSolo);

        /// @brief It checks if the ECS resources are loaded, and if not, it loads them
        /// @param isSolo If true, the client will be the only player in the room.
        void _updateEcsResources(bool isSolo);

        /// @brief It initializes the entities that are needed for the current state of the game
        void _updateEcsEntities();

        /// @brief It adds all the systems needed for the game to work
        /// @param isSolo if the game is in solo mode or not
        void _updateEcsSystems(bool isSolo);

        /// @brief It's a big switch case that handles all the messages that the client can
        /// receive from the server
        /// @param isSolo a boolean that tells if the client is alone in the room or not.
        /// @return A boolean.
        bool _answerProtocols(bool isSolo);

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
        void _initInGameButtons();

        /// @brief Init all the Writable and the linked actions
        void _initInGameWritables();

        /// @brief Ask the user to enter his Pseudonyme and password
        void _getClientPseudoAndPassword();

        /// @brief Init all the sprites needed for the player
        /// @param textureResource texture's map holding the texture and the corresponding key
        void _initPlayerTextures(graphicECS::SFML::Resources::GraphicsTextureResource &textureResource);

        /// @brief Init all the sprites needed for the enemies
        /// @param spritesList texture's map holding the texture and the corresponding key
        void _initSpriteForEnemies(graphicECS::SFML::Resources::GraphicsTextureResource &spritesList);

        /// @brief Init all the sprites needed for the projectiles
        /// @param textureResource texture's map holding the texture and the corresponding key
        void _initProjectilesTextures(graphicECS::SFML::Resources::GraphicsTextureResource &textureResource);

        /// @brief Init all the sprites needed for the backgrounds
        /// @param textureResource texture's map holding the texture and the corresponding key
        void _initBackgroundsTextures(graphicECS::SFML::Resources::GraphicsTextureResource &textureResource);

        /// @brief Init all the sprites needed for the Writable object
        /// @param textureResource texture's map holding the texture and the corresponding key
        void _initWritableTextures(graphicECS::SFML::Resources::GraphicsTextureResource &textureResource);

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

        /// @brief Start the connexion protocol and ask the server for a place inside the room
        void _startConnexionProtocol(void);

        /// @brief Answer the reception of a protocol 12
        void _protocol12Answer(CommunicatorMessage connexionResponse);

        /// @brief Answer the reception of a protocol 15
        /// @param connectionResponse The received response
        void _protocol15Answer(CommunicatorMessage connectionResponse);
    };
} // namespace client_data

#endif /* !CLIENT_HPP_ */
