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
                stopSound(world, sound);
            }
            if (sound.getStatus() == SoundName::PAUSED) {
                pauseSound(world, sound);
            }
            if (sound.getStatus() == SoundName::PLAY) {
                playSound(world, sound);
            }
        };

        std::for_each(joined.begin(), joined.end(), stopSound);
    }
} // namespace graphicECS::SFML::Systems
