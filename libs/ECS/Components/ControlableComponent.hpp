/*
** EPITECH PROJECT, 2022
** Project
** File description:
** ControlableComponent
*/

#ifndef CONTROLABLECOMPONENT_HPP_
#define CONTROLABLECOMPONENT_HPP_

#include "Component.hpp"

namespace ecs
{
    /// @brief The controlable class, defining if an entity is affected by the player's input
    class Controlable : public Component {
      public:
        /// @brief True if the corresponding entity is linked to the player
        bool IsControlable;

        /// @brief Constructor of the Controlable Component
        /// @param control true if the linked entity will take player's input
        Controlable(bool control) : IsControlable(control){};
        /// @brief Copy constructor of the Controlable Component
        /// @param old  the copy of the Controlable Component
        Controlable(const Controlable &old) : IsControlable(old.IsControlable){};

        /// @brief Default Destructor
        ~Controlable() = default;
    };
} // namespace ecs

#endif /* !CONTROLABLECOMPONENT_HPP_ */
