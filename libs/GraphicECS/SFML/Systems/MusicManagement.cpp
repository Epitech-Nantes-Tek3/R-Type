/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** MusicManagement
*/

#include "MusicManagement.hpp"

using namespace graphicECS::SFML::Components;

namespace graphicECS::SFML::Systems
{
    void MusicManagement::run(World &world)
    {
        std::vector<std::shared_ptr<ecs::Entity>> joined = world.joinEntities<MusicName>();

        auto stopMusic = [&world](std::shared_ptr<ecs::Entity> entityPtr) {
            MusicName music = entityPtr.get()->getComponent<MusicName>();

            if (music._status == MusicName::STOPED && world.getResource<MusicResource>()._musicsList.at(music.musicName)->getStatus() != sf::Music::Stopped) {
                world.getResource<MusicResource>()._musicsList.at(music.musicName)->stop();
            }
            if (music._status == MusicName::PAUSED && world.getResource<MusicResource>()._musicsList.at(music.musicName)->getStatus() != sf::Music::Paused) {
                world.getResource<MusicResource>()._musicsList.at(music.musicName)->pause();
            }
            if (music._status == MusicName::PLAYING && world.getResource<MusicResource>()._musicsList.at(music.musicName)->getStatus() != sf::Music::Playing) {
                world.getResource<MusicResource>()._musicsList.at(music.musicName)->play();
            }
        };
        std::for_each(joined.begin(), joined.end(), stopMusic);
    }
} // namespace graphicECS::SFML::Systems