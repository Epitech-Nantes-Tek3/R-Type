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
        std::vector<std::shared_ptr<ecs::Entity>> joined = world.joinEntities<SoundComponent>();

        auto stopSound = [&world](std::shared_ptr<ecs::Entity> entityPtr) {
            SoundComponent sound = entityPtr.get()->getComponent<SoundComponent>();

            if (sound._status == SoundComponent::STOPED
                && world.getResource<SoundResource>()._soundsList.at(sound.soundName)->getStatus()
                    != sf::Sound::Stopped) {
                world.getResource<SoundResource>()._soundsList.at(sound.soundName)->stop();
            }
            if (sound._status == SoundComponent::PAUSED
                && world.getResource<SoundResource>()._soundsList.at(sound.soundName)->getStatus()
                    != sf::Sound::Paused) {
                world.getResource<SoundResource>()._soundsList.at(sound.soundName)->pause();
            }
            if (sound._status == SoundComponent::PLAYING
                && world.getResource<SoundResource>()._soundsList.at(sound.soundName)->getStatus()
                    != sf::Sound::Playing) {
                world.getResource<SoundResource>()._soundsList.at(sound.soundName)->play();
            }
        };
        std::for_each(joined.begin(), joined.end(), stopSound);
    }
} // namespace graphicECS::SFML::Systems
