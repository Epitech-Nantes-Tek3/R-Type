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

        /// @brief This is the destructor of Component Class
        virtual ~Component() = default;

        /// @brief this function give the name of the component (itself)
        /// @return the name of itself
        const std::string getName() const { return this->_name; };

    protected:

        /// @brief This is the constructor of Component Class
        Component(const std::string name) : _name(name) {};

        /// @brief This is the constructor of Component Class
        Component(const std::string &name) : _name(name) {};

    private:
        const std::string _name;
    };
}
