/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** SoundManagement
*/

#include "SoundManagement.hpp"

using namespace graphicECS::SFML::Components;

namespace graphicECS::SFML::Systems
{
    void SoundManagement::run(World &world)
    {
        std::vector<std::shared_ptr<ecs::Entity>> joined = world.joinEntities<SoundName>();

        auto stopSound = [&world](std::shared_ptr<ecs::Entity> entityPtr) {
            SoundName sound = entityPtr.get()->getComponent<SoundName>();

            if (sound.getStatus() == SoundName::STOPED) {
                world.getResource<SoundResource>()._soundsList.at(sound.getName())->stop();
            }
            if (sound.getStatus() == SoundName::PAUSED) {
                world.getResource<SoundResource>()._soundsList.at(sound.getName())->pause();
            }
            if (sound.getStatus() == SoundName::PLAYING) {
                world.getResource<SoundResource>()._soundsList.at(sound.getName())->play();
            }
        };

        std::for_each(joined.begin(), joined.end(), stopSound);
    }
} // namespace graphicECS::SFML::Systems
