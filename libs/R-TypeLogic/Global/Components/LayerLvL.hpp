/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** LayerLvL
*/

#ifndef LAYERLVL_HPP_
#define LAYERLVL_HPP_

#include "Component/Component.hpp"

namespace ecs
{
    /// @brief This class LayerLvL is created in order to know the layer level of display.
    /// It will be used to order graphicals component to know in which order they will be displayed.
    class LayerLvL : public Component {
      public:
        /// @brief Enumeration of the different layers can be used
        enum layer_e { UNKNOWN, BACKGROUND, MIDDLE, DECORATION, OBSTACLE, BUTTON, ENEMY, PLAYER, PROJECTILE, LAYER_NUMBER };

        /// @brief The layer set on this component.
        layer_e layer;

        /// @brief Construct a new LayerLvL component.
        /// @param l The value to set on this component.
        LayerLvL(const layer_e l = UNKNOWN) : layer(l){};

        /// @brief Default destructor of this component.
        ~LayerLvL() = default;
    };
} // namespace ecs

#endif /* !LAYERLVL_HPP_ */
