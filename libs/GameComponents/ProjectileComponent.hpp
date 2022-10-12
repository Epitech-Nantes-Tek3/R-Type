/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** ProjectileComponent
*/

#ifndef PROJECTILECOMPONENT_HPP_
#define PROJECTILECOMPONENT_HPP_

#include "Component/Component.hpp"

namespace ecs
{
   /// @brief This Component specifies if an entity is a Projectile. This component specifies whether an entity is either friendly fire or enemy fire
   class Projectile : public Component {}; 
} // namespace ecs

#endif /* !PROJECTILECOMPONENT_HPP_ */
