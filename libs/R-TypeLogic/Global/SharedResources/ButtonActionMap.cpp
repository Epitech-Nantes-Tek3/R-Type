/*
** EPITECH PROJECT, 2022
** Project
** File description:
** ButtonActionMap
*/

#include "ButtonActionMap.hpp"

using namespace ecs;

ButtonActionMap::ButtonActionMap(const buttonAction_e &action, std::function<void(World &)> fctPtr)
{
    addAction(action, fctPtr);
}

void ButtonActionMap::addAction(const buttonAction_e newAction, std::function<void(World &)> fctPtr)
{
    _actionList.emplace(newAction, fctPtr);
}