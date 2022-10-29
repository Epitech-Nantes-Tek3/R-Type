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
        void run(World &world);

      private:

    };
} // namespace graphicECS::SFML::Systems

#endif /* !SOUNDMANAGEMENT_HPP_ */
