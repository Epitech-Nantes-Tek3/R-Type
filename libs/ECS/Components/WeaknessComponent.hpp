/*
** EPITECH PROJECT, 2022
** Project
** File description:
** WeaknessComponent
*/

#ifndef WEAKNESSCOMPONENT_HPP_
#define WEAKNESSCOMPONENT_HPP_

#include "Component.hpp"

namespace ecs
{

    /// @brief The Weakness component, to create a target for projectiles
    class Weakness : public Component {
      public:
        /// @brief The abscissa of the Weakness
        int x;
        /// @brief The ordinate of the Weakness
        int y;

        /// @brief Constructor of the Weakness component
        /// @param X the abscissa
        /// @param Y the ordinate
        Weakness(const int &X, const int &Y) : x(X), y(Y){};
        /// @brief Copy Constructor of the Weakness Component
        /// @param old The copy of the Weakness Component
        Weakness(const Weakness &old) : x(old.x), y(old.y) {};
        /// @brief Default Destructor
        ~Weakness() = default;
    };
} // namespace ecs

#endif /* !WEAKNESSCOMPONENT_HPP_ */
