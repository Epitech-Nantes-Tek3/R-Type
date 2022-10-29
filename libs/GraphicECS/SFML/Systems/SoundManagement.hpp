/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** SoundManagement
*/

#ifndef SOUNDMANAGEMENT_HPP_
#define SOUNDMANAGEMENT_HPP_

#include "GraphicECS/SFML/Components/SoundName.hpp"
#include "System/System.hpp"
#include "World/World.hpp"

namespace graphicECS::SFML::Systems
{
    struct SoundManagement : public System {
      public:

        /// @brief The run function of this system. It will be used by the world in the function runSystems.
        /// @param world The corresponding world on which run this system.
        void run(World &world);

      private:
        /// @brief This function Stoped the sound if it's status component is Stoped
        /// It also resets the playing position (unlike pause()).
        /// @param world The corresponding world on which run this system.
        /// @param sound The Entity Component of the song (to find it's name and status)
        inline void stopSound(World &world, SoundName &sound)
        {
            world.getResource<SoundResource>()._soundsList.at(sound.getName())->stop();
        };
        inline void pauseSound(World &world, SoundName &sound)
        {
            world.getResource<SoundResource>()._soundsList.at(sound.getName())->pause();
        };
        inline void playSound(World &world, SoundName &sound)
        {
            world.getResource<SoundResource>()._soundsList.at(sound.getName())->play();
        };
    };
} // namespace graphicECS::SFML::Systems

#endif /* !SOUNDMANAGEMENT_HPP_ */
