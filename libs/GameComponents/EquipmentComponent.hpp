/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** EquipmentComponent
*/

#ifndef EQUIPABLECOMPONENT_HPP_
#define EQUIPABLECOMPONENT_HPP_

#include "Component/Component.hpp"

namespace ecs
{
    /// @brief The Equipment class, giving bonuses to entities
    class Equipment : public Component {
      public:
        /// @brief The equipment type
        unsigned short typeId;

        /// @brief Constructor of the Equipment
        /// @param EquipId the id of the equipment (defined in the corresponding system)
        Equipment(unsigned short EquipId = 0) : typeId(EquipId){};
        /// @brief Default Constructor
        ~Equipment() = default;
    };
} // namespace ecs

#endif /* !EQUIPABLECOMPONENT_HPP_ */
