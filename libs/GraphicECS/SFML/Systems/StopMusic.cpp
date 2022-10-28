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
    std::vector<std::shared_ptr<ecs::Entity>> joined = world.joinEntities<Music>();

    auto makeParallax = [](std::shared_ptr<ecs::Entity> entityPtr) {
        MusicName musicname = entityPtr.get()->getComponent<Music>();
        MusicResource music = world.getResource<MusicResource>()

        if (musicname.getStatus() != MusicName::STOPED)
            musicname.setStatus(STOPED);
        // Recuperer la musique dans la shared Resource et la mettre en stoped
    };

    std::for_each(joined.begin(), joined.end(), makeParallax);

}