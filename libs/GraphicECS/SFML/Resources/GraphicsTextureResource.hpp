/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** GraphicsTextureResource
*/

#ifndef GRAPHICSTEXTURERESOURCE_HPP_
#define GRAPHICSTEXTURERESOURCE_HPP_

#include <SFML/Graphics.hpp>
#include <filesystem>
#include "Resource/Resource.hpp"
#include <unordered_map>

namespace graphicECS::SFML::Resources
{

    /// @brief This resource class stores a map of Graphical SFML textures to be set on Shapes.
    class GraphicsTextureResource : public ecs::Resource {
      public:
        /// @brief Enumeration of all available Textures
        enum textureName_e {
            UNDEFINED,
            PLAYER_STATIC_1,
            PLAYER_STATIC_2,
            PLAYER_STATIC_3,
            PLAYER_STATIC_4,
            PLAYER_STATIC_5,
            PLAYER_STATIC_6,
            PLAYER_STATIC_7,
            PLAYER_STATIC_8,
            PLAYER_UP,
            PLAYER_DOWN,
            ENEMY_STATIC,
            ENEMY_UP,
            ENEMY_DOWN,
            BACKGROUND_LAYER_1,
            BACKGROUND_LAYER_2,
            BACKGROUND_LAYER_3,
            OBSTACLE_1,
            OBSTACLE_2,
            OBSTACLE_3,
            PROJECTILE_ALLY,
            PROJECTILE_ENEMY_BASIC,
            PROJECTILE_ENEMY_FIRE,
            PROJECTILE_ENEMY_ELECTRIC,
            PROJECTILE_ENEMY_ICE,
            BUTTON,
            WRITABLE,
            WRITABLE_SELECTED,
            WRITABLE_BUTTON,
            NATURAL_PROJECTILE
        };

        /// @brief Name of map which contains Textures.
        using TexturesList = std::unordered_map<textureName_e, std::shared_ptr<sf::Texture>>;

        /// @brief Defauld Constructor of GraphicTextureResource.
        GraphicsTextureResource() = default;

        /// @brief Add a Texture from it's Texture Path passed as parameter
        /// @param texture_e Enum of the Texture
        /// @param texturePath The texture path to be used.
        /// @param position The position of the image to start getting the texture
        /// @param size The size on an image to get to create a texture
        inline GraphicsTextureResource(const textureName_e texture_e, const std::filesystem::path &texturePath,
            const sf::Vector2f &position = sf::Vector2f(0, 0), const sf::Vector2f &size = sf::Vector2f(0, 0))
        {
            addTexture(texture_e, texturePath, position, size);
        }

        /// @brief Add a texture to the TexturesList
        /// @param texture_e Enum which give the name of the Texture
        /// @param texturePath Path of the Texture
        void addTexture(const textureName_e texture_e, const std::filesystem::path &texturePath,
            const sf::Vector2f &position = sf::Vector2f(0, 0), const sf::Vector2f &size = sf::Vector2f(0, 0));

        /// @brief Default destructor of the class.
        ~GraphicsTextureResource() = default;

        TexturesList _texturesList;
    };
} // namespace graphicECS::SFML::Resources

#endif /* !GRAPHICSTEXTURERESOURCE_HPP_ */
