/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** World
*/

#include "World.hpp"
#include "Entity/Entity.hpp"

using namespace ecs;

Entity &World::addEntity()
{
    _entitiesList[_nextEntityId] = std::make_shared<Entity>(_nextEntityId);
    _nextEntityId++;
    return *(_entitiesList[_nextEntityId - 1].get());
}

Entity &World::getEntity(ID id) const
{
    EntitiesList::const_iterator it = _entitiesList.find(id);
    if (it == _entitiesList.end())
        throw std::logic_error("attempted to get a non-existent entity");
    return *(it->second.get());
}

void World::removeEntity(ID id)
{
    EntitiesList::const_iterator it = _entitiesList.find(id);
    if (it == _entitiesList.end())
        throw std::logic_error("attempted to remove a non-existent entity");
    _entitiesList.erase(it);
}

void World::runSystems()
{
    for (auto &it : _systemsList)
        it.second.get()->run(*this);
}
