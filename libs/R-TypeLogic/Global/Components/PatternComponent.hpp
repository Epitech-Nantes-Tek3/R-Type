/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** PaternComponent
*/

#ifndef PATERNCOMPONENT_HPP_
#define PATERNCOMPONENT_HPP_

#include <chrono>
#include <tuple>
#include <vector>
#include "Component/Component.hpp"

using namespace std::chrono;

namespace rtypelogic::global
{
    /// @brief The Movement component, used for mobiles entities
    class Pattern : public ecs::Component {
      public:
        /// @brief Vector of movements to execute
        std::vector<std::tuple<int, int>> pattern;
        /// @brief The changing movement frequency, iterate in the vector to have a new movement
        duration<double> changeFrequency;

        /// @brief Constructor of Patterns component
        /// @param directions vector of directions
        /// @param movingFrequency frequency of the iteration in the vector
        Pattern(const std::vector<std::tuple<int, int>> &directions = {},
            duration<double> movingFrequency = duration<double>(0))
            : pattern(directions), changeFrequency(movingFrequency){};
        /// @brief Default Destructor
        ~Pattern() = default;
    };
} // namespace rtypelogic::global

#endif /* !PATERNCOMPONENT_HPP_ */
