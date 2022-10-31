/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** SoundResources
*/

#include "SoundResource.hpp"

using namespace graphicECS::SFML::Resources;

void SoundResource::addSound(const SoundResource::sound_e sound_e, const std::filesystem::path &soundPath)
{
    sf::SoundBuffer buffer;
    sf::Sound sound;

    if (!buffer.loadFromFile(soundPath.string()))
        throw std::logic_error("LoadFromFile for load song buffer failed.");
    sound.setBuffer(buffer);
    _soundsList.emplace(sound_e, std::make_shared<sf::Sound>(sound));
}