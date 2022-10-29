/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** SoundManagement
*/

#ifndef SOUNDMANAGEMENT_HPP_
#define SOUNDMANAGEMENT_HPP_

#include "System/System.hpp"
#include "World/World.hpp"
#include "GraphicECS/SFML/Components/SoundName.hpp"

namespace graphicECS::SFML::Systems
{
    struct SoundManagement : public System {
      public:
        /// @brief The run function of this system. It will be used by the world in the function runSystems.
        /// @param world The corresponding world on which run this system.
        void run(World &world);

        /// @brief This function Stoped the sound if it's status component is STOPED
        /// It also resets the playing position (unlike pause()).
        /// @param world The corresponding world on which run this system.
        /// @param sound The Entity Component of the song (to find it's name and status)
        inline void stopSound(World &world, SoundName &sound)
        {
            world.getResource<SoundResource>()._soundsList.at(sound.getName())->stop();
        };

        /// @brief This function Paused the sound if it's status component is PAUSED
        /// @param world The corresponding world on which run this system.
        /// @param sound The Entity Component of the song (to find it's name and status)
        inline void pauseSound(World &world, SoundName &sound)
        {
            world.getResource<SoundResource>()._soundsList.at(sound.getName())->pause();
        };

        /// @brief This function Play the sound if it's status component is PLAY
        /// @param world The corresponding world on which run this system.
        /// @param sound The Entity Component of the song (to find it's name and status)
        inline void playSound(World &world, SoundName &sound)
        {
            world.getResource<SoundResource>()._soundsList.at(sound.getName())->play();
        };
    };
} // namespace graphicECS::SFML::Systems

#endif /* !SOUNDMANAGEMENT_HPP_ */
