/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** Component
*/

#pragma once

#include <string>

namespace ecs
{
    class Component
    {
    public:
    
        /// @brief This is the constructor of Component Class
        Component();

        /// @brief This is the destructor of Component Class
        ~Component();

        /// @brief this function give the name of the component (itself)
        /// @return the name of itself
        std::string getName() { return this->_name; };

    protected:
    private:
        std::string _name;
    };
}
