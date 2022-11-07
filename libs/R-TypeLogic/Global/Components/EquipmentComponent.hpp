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
    /// @brief The Equipment component, giving bonuses to entities
    /// It's a networkable component.
    class Equipment : public Component {
      public:
        /// @brief The equipment type
        unsigned short typeId;
        /// @brief The network status of the component. True if it has been modified since it was last sent.
        bool modified;

        /// @brief If the server need to resend it to everyone
        bool sendToEveryone;

        /// @brief Id of the client to delete from the Database after sending the death component. 1000 if no client
        /// needed to be deleted
        unsigned short clientToDelete;

        /// @brief Constructor of the Equipment
        /// @param EquipId the id of the equipment (defined in the corresponding system)
        Equipment(unsigned short EquipId = 0)
            : typeId(EquipId), modified(false), sendToEveryone(false), clientToDelete(1000){};
        /// @brief Default Constructor
        ~Equipment() = default;
    };
} // namespace ecs

#endif /* !EQUIPABLECOMPONENT_HPP_ */
