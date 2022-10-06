/*
** EPITECH PROJECT, 2022
** Project
** File description:
** WeaknessComponent
*/

#ifndef WEAKNESSCOMPONENT_HPP_
#define WEAKNESSCOMPONENT_HPP_

#include "Component/Component.hpp"
#include <tuple>

namespace ecs
{
    /// @brief The Weakness component, to create a target for projectiles
    class Weakness : public Component {
      public:
        /// @brief The center of the Weakness's circle (with abscissa and ordinate)
        std::tuple<double, double> center;
        /// @brief The radius of the Weakness's circle
        unsigned short radius;

        /// @brief Constructor of the Weakness component
        /// @param newCenter the new center
        /// @param newRadius the new radius
        Weakness(std::tuple<double, double> newCenter, unsigned short newRadius) : center(newCenter), radius(newRadius) {};
        /// @brief Copy Constructor of the Weakness Component
        /// @param old The copy of the Weakness Component
        Weakness(const Weakness &old) : center(old.center), radius(old.radius) {};
        /// @brief Default Destructor
        ~Weakness() = default;
    };
} // namespace ecs

#endif /* !WEAKNESSCOMPONENT_HPP_ */
