/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** SoundResources
*/

#include "SoundResource.hpp"

using namespace ecs;

void SoundResource::addSound(const soundName_e sound_e, const std::filesystem::path &soundPath)
{
    sf::SoundBuffer buffer;
    sf::Sound sound;

    if (!buffer.loadFromFile(soundPath))
        // throw error
        void();
    sound.setBuffer(buffer);
    _soundsList.emplace(sound_e, std::make_shared<sf::Sound>(sound));
}
