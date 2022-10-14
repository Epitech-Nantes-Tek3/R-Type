/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** GraphicsTextureResource
*/

#include "GraphicsTextureResource.hpp"

using namespace ecs;

void GraphicsTextureResource::addTexture(const textureName_e texture_e, const std::filesystem::path &texturePath)
{
    sf::Texture t;

    t.loadFromFile(texturePath);
    _texturesList.emplace(texture_e, std::make_shared<sf::Texture>(t));
}