/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** MusicResource
*/

#include "MusicResource.hpp"

using namespace ecs;

void MusicResource::addMusic(const musicName_e music_e, const std::filesystem::path &musicPath)
{
    sf::Music music;

    if (!music.openFromFile(musicPath)) {
        // throw error...
    }
    _musicsList.emplace(music_e, std::make_shared<sf::Sound>(music));
}