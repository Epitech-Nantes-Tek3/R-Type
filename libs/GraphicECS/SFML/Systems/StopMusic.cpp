/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** StopMusic
*/

#include "StopMusic.hpp"
#include "GraphicECS/SFML/Components/MusicName.hpp"

using namespace graphicECS::SFML::Systems;
using namespace graphicECS::SFML::Components;

void stopMusic(World &world, MusicName &music) { world.getResource<MusicResource>()._musicsList.at(music.getName())->stop(); }

void StopMusic::run(World &world)
{
    std::vector<std::shared_ptr<ecs::Entity>> joined = world.joinEntities<MusicName>();

    auto stopMusic = [&world](std::shared_ptr<ecs::Entity> entityPtr) {
        MusicName music = entityPtr.get()->getComponent<MusicName>();

        if (music.getStatus() == MusicName::STOPED) {
            stopMusic(world, music);
        }
    };

    std::for_each(joined.begin(), joined.end(), stopMusic);
}