/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** EnemyComponent
*/

#ifndef ENEMYCOMPONENT_HPP_
#define ENEMYCOMPONENT_HPP_

#include "Component/Component.hpp"

namespace ecs
{
    /// @brief Enemy Component allows an entity to be used as an Enemy
    class Enemy : public Component {
        public:
            /// @brief Enumeration of all current types of mob
            enum type_e {BASIC, FIRE, ELECTRIC, ICE};

            /// @brief The type of enemy, useful for the pattern and generated projectiles
            unsigned short enemyType;

            /// @brief Construct an Enemy with its type
            Enemy(type_e newType = BASIC) : enemyType(newType) {};

            /// @brief Default Destructor
            ~Enemy() = default;
    };
} // namespace ecs

#endif /* !ENEMYCOMPONENT_HPP_ */

