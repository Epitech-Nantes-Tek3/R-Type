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
#include <unordered_map>
#include "Resource/Resource.hpp"

namespace ecs
{

    /// @brief This resource class stores a map of Graphical SFML textures to be set on Shapes.
    class GraphicsTextureResource : public Resource {
      public:
        /// @brief Enumeration of all available Textures
        enum textureName_e {
            UNDEFINED,
            PLAYER_STATIC,
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
            PROJECTILE,
            BUTTON,
            NATURAL_PROJECTILE
        };

        /// @brief Name of map which contains Textures.
        using TexturesList = std::unordered_map<textureName_e, std::shared_ptr<sf::Texture>>;

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
} // namespace ecs

#endif /* !GRAPHICSTEXTURERESOURCE_HPP_ */
