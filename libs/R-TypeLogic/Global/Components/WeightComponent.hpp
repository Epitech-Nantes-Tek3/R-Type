/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** WeightComponent
*/

#ifndef WEIGHTCOMPONENT_HPP_
#define WEIGHTCOMPONENT_HPP_

#include "Component/Component.hpp"

namespace rtypelogic::global
{
    /// @brief The Weight class, almost used for everything, used in gravity system
    class Weight : public ecs::Component {
      public:
        /// @brief weight of the entity
        short weight;

        /// @brief Constructor of the Weight Component
        /// @param newWeight the weight
        Weight(short newWeight = 0) : weight(newWeight){};
        /// @brief Default Destructor
        ~Weight() = default;
    };
} // namespace rtypelogic::global

#endif /* !WEIGHTCOMPONENT_HPP_ */
