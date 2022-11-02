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
            SoundComponent soundComponent = entityPtr.get()->getComponent<SoundComponent>();
            sf::Sound sound;

            sound.setBuffer(*world.getResource<SoundResource>()._soundsList.at(soundComponent.sound_e));

            if (soundComponent._status == SoundComponent::STOPED && sound.getStatus() != sf::Sound::Stopped) {
                sound.stop();
            }
            if (soundComponent._status == SoundComponent::PAUSED && sound.getStatus() != sf::Sound::Paused) {
                sound.pause();
            }
            if (soundComponent._status == SoundComponent::PLAYING && sound.getStatus() != sf::Sound::Playing) {
                 sound.play();
            }
        };
        std::for_each(joined.begin(), joined.end(), stopSound);
    }
} // namespace graphicECS::SFML::Systems
