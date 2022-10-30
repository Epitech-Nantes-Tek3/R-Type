/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** SoundManagement
*/

#include "SoundManagement.hpp"

using namespace graphicECS::SFML::Components;
using namespace graphicECS::SFML::Resources;

namespace graphicECS::SFML::Systems
{
    void SoundManagement::run(World &world)
    {
        std::vector<std::shared_ptr<ecs::Entity>> joined = world.joinEntities<SoundName>();

        auto stopSound = [&world](std::shared_ptr<ecs::Entity> entityPtr) {
            SoundName sound = entityPtr.get()->getComponent<SoundName>();

         if (sound._status == SoundName::STOPED && world.getResource<SoundResource>()._soundsList.at(sound.name)->_status != sf::Sound::Stopped) {
                world.getResource<SoundResource>()._soundsList.at(sound.soundName)->stop();
            }
            if (sound._status == SoundName::PAUSED && world.getResource<SoundResource>()._soundsList.at(sound.soundName)->_status != sf::Sound::Paused) {
                world.getResource<SoundResource>()._soundsList.at(sound.soundName)->pause();
            }
            if (sound._status == SoundName::PLAYING && world.getResource<SoundResource>()._soundsList.at(sound.soundName)->_status != sf::Sound::Playing) {
                world.getResource<SoundResource>()._soundsList.at(sound.soundName)->play();
            }
        };

        std::for_each(joined.begin(), joined.end(), stopSound);
    }
} // soundNamespace graphicECS::SFML::Systems
