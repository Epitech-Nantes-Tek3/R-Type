/*
** EPITECH PROJECT, 2022
** Project
** File description:
** PaternComponent
*/

#ifndef PATERNCOMPONENT_HPP_
#define PATERNCOMPONENT_HPP_

#include "Component/Component.hpp"
#include <vector>
#include <tuple>
#include <chrono>

using namespace std::chrono;

namespace ecs
{
    /// @brief The Movement component, used for mobiles entities
    class Pattern : public Component {
      public:
        /// @brief Vector of movements to execute
        std::vector<std::tuple<int, int>> pattern;
        /// @brief The changing movement frequency, iterate in the vector to have a new movement
        duration<double> changeFrequency;

        /// @brief Constructor of Patterns component
        /// @param directions vector of directions
        /// @param movingFrequency frequency of the iteration in the vector
        Pattern(const std::vector<std::tuple<int, int>> &directions, duration<double> movingFrequency) : pattern(directions), changeFrequency(movingFrequency) {};
        /// @brief Copy Constructor of the Pattern Component
        /// @param old The copy of the Pattern Component
        Pattern(const Pattern &old) : pattern(old.pattern), changeFrequency(old.changeFrequency) {};
        /// @brief Default Destructor
        ~Pattern() = default;
    };
} // namespace ecs

#endif /* !PATERNCOMPONENT_HPP_ */
