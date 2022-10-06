/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** SizeComponent
*/

#ifndef SIZECOMPONENT_HPP_
#define SIZECOMPONENT_HPP_

#include "Component/Component.hpp"

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
        Size(const int &X = 0, const int &Y = 0) : x(X), y(Y){};
        /// @brief Default Destructor
        ~Size() = default;
    };
} // namespace ecs

#endif /* !SIZECOMPONENT_HPP_ */
