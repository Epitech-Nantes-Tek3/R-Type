/*
** EPITECH PROJECT, 2022
** Project
** File description:
** SizeComponent
*/

#ifndef SIZECOMPONENT_HPP_
#define SIZECOMPONENT_HPP_

#include "Component.hpp"

namespace ecs
{
    /// @brief The Size component, almost used for everything
    class Size : public Component {
      public:
        /// @brief The size's length
        int x;
        /// @brief The size's lenght
        int y;

        /// @brief Constructor of the Size component
        /// @param X the length
        /// @param Y the lenght
        Size(const int &X, const int &Y) : x(X), y(Y){};
        /// @brief Copy Constructor of the Size Component
        /// @param old The copy of the Size Component
        Size(const Size &old) : x(old.x), y(old.y) {};
        /// @brief Default Destructor
        ~Size() = default;
    };
} // namespace ecs

#endif /* !SIZECOMPONENT_HPP_ */
