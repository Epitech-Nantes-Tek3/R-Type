/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** WeaknessComponent
*/

#ifndef WEAKNESSCOMPONENT_HPP_
#define WEAKNESSCOMPONENT_HPP_

#include <array>
#include "Component/Component.hpp"

namespace rtypelogic::global
{
    /// @brief The Weakness component, to create a target for projectiles
    class Weakness : public ecs::Component {
      public:
        /// @brief The center of the Weakness's circle (with abscissa and ordinate)
        std::array<double, 2> center;
        /// @brief The radius of the Weakness's circle
        unsigned short radius;

        /// @brief Constructor of the Weakness component
        /// @param newCenter the new center
        /// @param newRadius the new radius
        Weakness(std::array<double, 2> newCenter = {0, 0}, unsigned short newRadius = 0)
            : center(newCenter), radius(newRadius){};
        /// @brief Default Destructor
        ~Weakness() = default;
    };
} // namespace rtypelogic::global

#endif /* !WEAKNESSCOMPONENT_HPP_ */
