/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** UserConnection
*/

#include "UserConnection.hpp"
#include "ButtonAction.hpp"
#include "Error/Error.hpp"
#include "GraphicECS/SFML/Components/ActionQueueComponent.hpp"
#include "GraphicECS/SFML/Components/AllowControllerComponent.hpp"
#include "GraphicECS/SFML/Components/AllowMouseAndKeyboardComponent.hpp"
#include "GraphicECS/SFML/Components/ControllerButtonInputComponent.hpp"
#include "GraphicECS/SFML/Components/ControllerJoystickInputComponent.hpp"
#include "GraphicECS/SFML/Components/KeyboardInputComponent.hpp"
#include "GraphicECS/SFML/Components/MouseInputComponent.hpp"
#include "GraphicECS/SFML/Components/TextureName.hpp"
#include "GraphicECS/SFML/Components/WritableContentComponent.hpp"
#include "GraphicECS/SFML/Resources/GraphicsFontResource.hpp"
#include "GraphicECS/SFML/Resources/GraphicsTextureResource.hpp"
#include "GraphicECS/SFML/Resources/MusicResource.hpp"
#include "GraphicECS/SFML/Resources/RenderWindowResource.hpp"
#include "GraphicECS/SFML/Systems/AnimationSystem.hpp"
#include "GraphicECS/SFML/Systems/DrawComponents.hpp"
#include "GraphicECS/SFML/Systems/InputManagement.hpp"
#include "GraphicECS/SFML/Systems/MusicManagement.hpp"
#include "GraphicECS/SFML/Systems/ParallaxSystem.hpp"
#include "GraphicECS/SFML/Systems/SfObjectFollowEntitySystem.hpp"
#include "GraphicECS/SFML/Systems/SoundManagement.hpp"
#include "Transisthor/TransisthorECSLogic/Client/Systems/SendNewlyCreatedToServer.hpp"
#include "Transisthor/TransisthorECSLogic/Client/Systems/SendToServer.hpp"
#include "R-TypeLogic/EntityManipulation/ButtonManipulation/SharedResources/ButtonActionMap.hpp"
#include "R-TypeLogic/EntityManipulation/ButtonManipulation/SharedResources/GameStates.hpp"
#include "R-TypeLogic/EntityManipulation/ButtonManipulation/SharedResources/MenuStates.hpp"
#include "R-TypeLogic/EntityManipulation/CreateEntitiesFunctions/CreateButton.hpp"
#include "R-TypeLogic/EntityManipulation/CreateEntitiesFunctions/CreateWritable.hpp"
#include "R-TypeLogic/Global/SharedResources/GameClock.hpp"
#include "R-TypeLogic/Global/SharedResources/Random.hpp"
#include "R-TypeLogic/Global/Systems/DeathSystem.hpp"
#include "R-TypeLogic/Global/Systems/MovementSystem.hpp"
#include "R-TypeLogic/Global/Systems/UpdateClockSystem.hpp"

using namespace client_data;
using namespace graphicECS::SFML::Resources;
using namespace graphicECS::SFML::Systems;
using namespace graphicECS::SFML::Components;

UserConnection::UserConnection()
{
    _pseudo = "";
    _password = "";
    _world = std::make_shared<World>(1);
}

UserConnection::~UserConnection() {}

void UserConnection::_loadResourcesUserConnection()
{
    _world->addResource<RandomDevice>()
        .addResource<GameClock>()
        .addResource<GameStates>()
        .addResource<RenderWindowResource>("Login", sf::VideoMode(360, 640, 32))
        .addResource<GraphicsFontResource>("assets/fonts/arial.ttf")
        .addResource<MusicResource>(MusicResource::music_e::BACKGROUNDTHEME, "assets/Musics/music_background.wav")
        .addResource<MenuStates>(MenuStates::IN_GAME)
        .addResource<ButtonActionMap>(
            ButtonActionMap::WRITABLE_BUTTON, std::function<void(World &, Entity &)>(writableButtonAction))
        .addResource<GraphicsTextureResource>(GraphicsTextureResource::BUTTON, "assets/EpiSprite/r-typesheet11.gif",
            sf::Vector2f(34, 0), sf::Vector2f(34, 34));
    _world->getResource<GraphicsTextureResource>().addTexture(
        GraphicsTextureResource::WRITABLE, "assets/EpiSprite/r-typesheet11.gif");
    _world->getResource<GraphicsTextureResource>().addTexture(
        GraphicsTextureResource::WRITABLE_BUTTON, "assets/EpiSprite/r-typesheet11.gif");
    _world->getResource<GraphicsTextureResource>().addTexture(
        GraphicsTextureResource::WRITABLE_SELECTED, "assets/EpiSprite/r-typesheet11.gif");
    _world->getResource<ButtonActionMap>().addAction(
        ButtonActionMap::WRITABLE, std::function<void(World &, Entity &)>(selectAWritable));
}

void UserConnection::_loadSystemsUserConnection()
{
    _world->addSystem<UpdateClock>()
        .addSystem<DeathSystem>()
        .addSystem<DrawComponents>()
        .addSystem<InputManagement>()
        .addSystem<SendToServer>()
        .addSystem<SendNewlyCreatedToServer>()
        .addSystem<SfObjectFollowEntitySystem>()
        .addSystem<Parallax>()
        .addSystem<Movement>()
        .addSystem<AnimationSystem>()
        .addSystem<MusicManagement>()
        .addSystem<SoundManagement>();
}

void UserConnection::_setInputUserConnection(ecs::Entity &entity)
{
    entity.getComponent<MouseInputComponent>().MouseMapActions.emplace(
        std::make_pair<sf::Mouse::Button, std::pair<ActionQueueComponent::inputAction_e, float>>(
            sf::Mouse::Button::Left,
            std::make_pair<ActionQueueComponent::inputAction_e, float>(ActionQueueComponent::BUTTON_CLICK, 0)));
}

void UserConnection::_loadEntitiesUserConnection(
    std::size_t &buttonSendId, std::size_t &buttonPseudoId, std::size_t &buttonPasswordId)
{
    ecs::Entity &inputsEntity = _world->addEntity()
                                    .addComponent<MouseInputComponent>()
                                    .addComponent<KeyboardInputComponent>()
                                    .addComponent<ControllerButtonInputComponent>()
                                    .addComponent<ControllerJoystickInputComponent>()
                                    .addComponent<ActionQueueComponent>()
                                    .addComponent<AllowMouseAndKeyboardComponent>()
                                    .addComponent<AllowControllerComponent>();

    _setInputUserConnection(inputsEntity);
    sf::RenderWindow &window = _world->getResource<RenderWindowResource>().window;
    buttonPseudoId = createNewWritable(
        *(_world.get()), window.getSize().x / 2 - 100, window.getSize().y / 5 - 25, 200, 50, MenuStates::IN_GAME);
    buttonPasswordId = createNewWritable(
        *(_world.get()), window.getSize().x / 2 - 100, window.getSize().y / 5 * 2 - 25, 200, 50, MenuStates::IN_GAME);
    buttonSendId = _world->addEntity()
                       .addComponent<Button>()
                       .addComponent<TextureName>(GraphicsTextureResource::BUTTON)
                       .addComponent<GraphicsRectangleComponent>()
                       .addComponent<GraphicsTextComponent>(_world->getResource<GraphicsFontResource>().font, "Send",
                           window.getSize().x / 2 - 100, window.getSize().y / 5 * 4 - 25)
                       .addComponent<Size>(200, 50)
                       .addComponent<Position>(window.getSize().x / 2 - 100, window.getSize().y / 5 * 4 - 25)
                       .addComponent<LayerLvL>(LayerLvL::WRITABLE)
                       .addComponent<ActionName>(ButtonActionMap::WRITABLE)
                       .addComponent<DisplayState>(MenuStates::IN_GAME)
                       .getId();
    _world->addEntity()
        .addComponent<Button>()
        .addComponent<GraphicsTextComponent>(_world->getResource<GraphicsFontResource>().font, "Select password",
            window.getSize().x / 2 - 100, window.getSize().y / 5 * 2 - 25)
        .addComponent<Size>(200, 50)
        .addComponent<Position>(window.getSize().x / 2 - 100, window.getSize().y / 5 * 2 - 25)
        .addComponent<LayerLvL>(LayerLvL::WRITABLE)
        .addComponent<ActionName>(ButtonActionMap::WRITABLE)
        .addComponent<DisplayState>(MenuStates::IN_GAME);
    _world->addEntity()
        .addComponent<Button>()
        .addComponent<GraphicsTextComponent>(_world->getResource<GraphicsFontResource>().font, "Select pseudo",
            window.getSize().x / 2 - 100, window.getSize().y / 5 - 25)
        .addComponent<Size>(200, 50)
        .addComponent<Position>(window.getSize().x / 2 - 100, window.getSize().y / 5 - 25)
        .addComponent<LayerLvL>(LayerLvL::WRITABLE)
        .addComponent<ActionName>(ButtonActionMap::WRITABLE)
        .addComponent<DisplayState>(MenuStates::IN_GAME);
}

void UserConnection::_runSystemsUserConnection(std::size_t buttonSendId)
{
    ecs::Entity &buttonSend = _world->getEntity(buttonSendId);

    while (_world->containsResource<RenderWindowResource>()
        && _world->getResource<RenderWindowResource>().window.isOpen()) {
        _world->runSystems();
        if (buttonSend.getComponent<Button>().IsClicked) {
            buttonSend.getComponent<Button>().IsClicked = false;
            break;
        }
    }
}

void UserConnection::userConnection()
{
    std::size_t buttonSendId = 0;
    std::size_t buttonPseudoId = 0;
    std::size_t buttonPasswordId = 0;
    bool validUserInformation = false;

    _loadResourcesUserConnection();
    _loadSystemsUserConnection();
    _loadEntitiesUserConnection(buttonSendId, buttonPseudoId, buttonPasswordId);
    while (!validUserInformation && _world->containsResource<RenderWindowResource>()
        && _world->getResource<RenderWindowResource>().window.isOpen()) {
        _runSystemsUserConnection(buttonSendId);
        _pseudo = _world->getEntity(buttonPseudoId).getComponent<WritableContent>().content;
        _password = _world->getEntity(buttonPasswordId).getComponent<WritableContent>().content;
        if (_pseudo.size() != 5 || _password.size() != 5) {
            _pseudo = "";
            _password = "";
            throw error_lib::RTypeError("User connection invalid size");
        } else {
            validUserInformation = true;
        }
    }
}

const std::string &UserConnection::getPseudo() const { return _pseudo; }

const std::string &UserConnection::getPassword() const { return _password; }
