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
        void(world);
    }
} // namespace graphicECS::SFML::Systems

        // std::vector<std::shared_ptr<ecs::Entity>> joined = world.joinEntities<MusicName>();

        // auto stopMusic = [&world](std::shared_ptr<ecs::Entity> entityPtr) {
        //     MusicName music = entityPtr.get()->getComponent<MusicName>();

        //     if (music.getStatus() == MusicName::STOPED) {
        //         world.getResource<MusicResource>()._musicsList.at(music.getName())->stop();
        //     }
        //     if (music.getStatus() == MusicName::PAUSED) {
        //         world.getResource<MusicResource>()._musicsList.at(music.getName())->pause();
        //     }
        //     if (music.getStatus() == MusicName::PLAYING) {
        //         world.getResource<MusicResource>()._musicsList.at(music.getName())->play();
        //     }
        // };

        // std::for_each(joined.begin(), joined.end(), stopMusic);
