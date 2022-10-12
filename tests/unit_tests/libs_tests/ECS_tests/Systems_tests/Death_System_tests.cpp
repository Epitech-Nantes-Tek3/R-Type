/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** Death_System_tests
*/


#include <criterion/criterion.h>
#include "World/World.hpp"
#include "Entity/Entity.hpp"
#include "GameSystems/DeathSystem.hpp"
#include "GameEntityManipulation/CreateEntitiesFunctions/CreateProjectile.hpp"
#include "GameComponents/DeathComponent.hpp"
#include "GameComponents/ProjectileComponent.hpp"

using namespace ecs;

Test(Death_system, kill_entity)
{
    World world(1);

    createNewProjectile(world, 10, 10, 1, 1, 10);
    
    // world.getEntity(1).getComponent<Life>().lifePoint = 0;
    // world.getEntity(2).getComponent<Life>().lifePoint = 0;
    // world.getEntity(3).getComponent<Life>().lifePoint = 0;

    std::vector<std::shared_ptr<ecs::Entity>> joined = world.joinEntities<Projectile>();

    world.getEntity(1).addComponent<Death>();

    world.addSystem<DeathSystem>();

    world.runSystems();

    std::vector<std::shared_ptr<ecs::Entity>> death_joined = world.joinEntities<Projectile>();

    cr_assert_eq(1, joined.size());
    cr_assert_eq(0, death_joined.size());
}

Test(Death_system, kill_entities)
{
    World world(1);

    createNewProjectile(world, 10, 10, 1, 1, 10);
    createNewProjectile(world, 10, 10, 1, 1, 10);
    createNewProjectile(world, 10, 10, 1, 1, 10);
    
    // world.getEntity(1).getComponent<Life>().lifePoint = 0;
    // world.getEntity(2).getComponent<Life>().lifePoint = 0;
    // world.getEntity(3).getComponent<Life>().lifePoint = 0;

    std::vector<std::shared_ptr<ecs::Entity>> joined = world.joinEntities<Projectile>();

    world.getEntity(2).addComponent<Death>();

    world.addSystem<DeathSystem>();

    world.runSystems();

    std::vector<std::shared_ptr<ecs::Entity>> death_joined = world.joinEntities<Projectile>();

    cr_assert_eq(3, joined.size());
    cr_assert_eq(2, death_joined.size());
}