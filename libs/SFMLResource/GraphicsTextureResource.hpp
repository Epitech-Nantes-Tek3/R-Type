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

namespace ecs
{

    /// @brief This resource class stores a Graphical SFML texture to be set on a rectangle shape resource.
    /// This class is created in order to set a texture on a rectangle shape resource.
    class GraphicsTextureResource : public Resource {
      public:
        /// @brief All the possible Textures
        enum textureName_e { UNDEFINED, PLAYER, PLAYER_UP, PLAYER_DOWN };

        /// @brief Name of map which contains Textures. It's sorted by the name of the Texture and the Texture
        using TexturesList = std::unordered_map<textureName_e, std::shared_ptr<sf::Texture>>;

        /// @brief Default constructor of the class.
        GraphicsTextureResource() = default;

        /// @brief Create a texture from the path to an image.
        /// @param texturePath The texture path to be used.
        inline GraphicsTextureResource(const textureName_e texture_e, const std::filesystem::path &texturePath)
        {
            addTexture(texture_e, texturePath);
        }

        /// @brief Add a texture to the TexturesList
        /// @param texture_e Enum which give the name of the Texture
        /// @param texturePath Path of the Textrue
        inline void addTexture(const textureName_e texture_e, const std::filesystem::path &texturePath)
        {
            _texturesList.emplace(texture_e, std::make_shared<sf::Texture>()->loadFromFile(texturePath));
        }

        /// @brief Default destructor of the class.
        ~GraphicsTextureResource() = default;

      private:
        TexturesList _texturesList;
    };
} // namespace ecs

#endif /* !GRAPHICSTEXTURERESOURCE_HPP_ */
