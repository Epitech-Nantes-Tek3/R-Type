/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** StopMusic
*/

#include "StopMusic.hpp"

using namespace graphicECS::SFML::Systems;
using namespace graphicECS::SFML::Components;

void StopMusic::run(World &world)
{
    std::vector<std::shared_ptr<ecs::Entity>> joined = world.joinEntities<MusicName>();

    auto stopMusic = [world](std::shared_ptr<ecs::Entity> entityPtr) {
        MusicName music = entityPtr.get()->getComponent<MusicName>(); // get Commponent
        MusicResource &musicsList = world.getResource<MusicResource>(); // get all resources
       
        if (music.getStatus() != MusicName::STOPED)
            music.setStatus(MusicName::STOPED);

        musicsList._musicsList.at(music.getName())->stop();
    };

    std::for_each(joined.begin(), joined.end(), stopMusic);

}