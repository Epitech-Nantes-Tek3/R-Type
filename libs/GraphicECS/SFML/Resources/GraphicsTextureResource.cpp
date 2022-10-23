/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** GraphicsTextureResource
*/

#include "GraphicsTextureResource.hpp"

using namespace graphic::sfml;

void GraphicsTextureResource::addTexture(const textureName_e texture_e, const std::filesystem::path &texturePath,
    const sf::Vector2f &position, const sf::Vector2f &size)
{
    sf::Texture t;

    t.loadFromFile(texturePath.string(), sf::IntRect(sf::Vector2i(position), sf::Vector2i(size)));
    _texturesList.emplace(texture_e, std::make_shared<sf::Texture>(t));
}
