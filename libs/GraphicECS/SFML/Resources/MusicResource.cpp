/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** MusicResource
*/

#include "MusicResource.hpp"

using namespace graphicECS::SFML::Resources;

void MusicResource::addMusic(const musicName_e music_e, const std::filesystem::path &musicPath)
{
    std::shared_ptr<sf::Music> music = std::make_shared<sf::Music>();

    if (!music->openFromFile(musicPath.string())) {
        throw std::logic_error("LoadFromFile for load song buffer failed.");
    }
    _musicsList.emplace(music_e, music);
}