/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** AssociatedIdComponent
*/

#ifndef ASSOCIATEDIDCOMPONENT_HPP_
#define ASSOCIATEDIDCOMPONENT_HPP_

#include <vector>

namespace graphicECS::SFML::Components
{
    /// @brief This component class stores all the associated entity id
    class AssociatedId : public ecs::Component {
      public:
        /// @brief A string containing all the typed content
        std::vector<std::size_t> idList;

        /// @brief Constructor of AssociatedIdComponent.
        /// @param idListParam list of all the associated id
        inline AssociatedId(std::vector<std::size_t> idListParam = {}) { idList = idListParam; };

        /// @brief Destroy the Associated Id object
        ~AssociatedId() = default;
    };
} // namespace graphicECS::SFML::Components

#endif /* !ASSOCIATEDIDCOMPONENT_HPP_ */
