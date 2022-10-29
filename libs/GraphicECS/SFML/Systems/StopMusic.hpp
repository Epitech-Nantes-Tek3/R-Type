/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** StopMusic
*/

#ifndef STOPMUSIC_HPP_
#define STOPMUSIC_HPP_

#include "System/System.hpp"
#include "World/World.hpp"

namespace graphicECS::SFML::Systems
{
    struct StopMusic : public System {
        void run(World &world) override final;
    }; 
} // namespace graphicECS::SFML::Systems


#endif /* !STOPMUSIC_HPP_ */
