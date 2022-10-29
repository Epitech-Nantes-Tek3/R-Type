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
        void run(World &world);

      private:
        inline void stopSound(World &world, SoundName &sound)
        {
            world.getResource<SoundResource>()._soundsList.at(sound.getName())->stop();
        };
        inline void pauseSound(World &world, SoundName &sound)
        {
            world.getResource<SoundResource>()._soundsList.at(sound.getName())->pause();
        };
    };
} // namespace graphicECS::SFML::Systems

#endif /* !SOUNDMANAGEMENT_HPP_ */
