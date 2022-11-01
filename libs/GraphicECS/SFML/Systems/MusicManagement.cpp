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
        std::vector<std::shared_ptr<ecs::Entity>> joined = world.joinEntities<MusicComponent>();

        auto stopMusic = [&world](std::shared_ptr<ecs::Entity> entityPtr) {
            MusicComponent music = entityPtr.get()->getComponent<MusicComponent>();

            if (music._status == MusicComponent::STOPED
                && world.getResource<MusicResource>()._musicsList.at(music.music_e)->getStatus()
                    != sf::Music::Stopped) {
                world.getResource<MusicResource>()._musicsList.at(music.music_e)->stop();
            }
            if (music._status == MusicComponent::PAUSED
                && world.getResource<MusicResource>()._musicsList.at(music.music_e)->getStatus() != sf::Music::Paused) {
                world.getResource<MusicResource>()._musicsList.at(music.music_e)->pause();
            }
            if (music._status == MusicComponent::PLAYING
                && world.getResource<MusicResource>()._musicsList.at(music.music_e)->getStatus()
                    != sf::Music::Playing) {
                world.getResource<MusicResource>()._musicsList.at(music.music_e)->play();
            }
        };
        std::for_each(joined.begin(), joined.end(), stopMusic);
    }
} // namespace graphicECS::SFML::Systems