/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** CollidableSystemTest
*/

#include <criterion/criterion.h>
#include "Entity/Entity.hpp"
#include "GameComponents/PositionComponent.hpp"
#include "GameComponents/SizeComponent.hpp"
#include "GameComponents/DamageComponent.hpp"
#include "GameComponents/CollidableComponent.hpp"
#include "GameComponents/LifeComponent.hpp"
#include "GameComponents/PlayerComponent.hpp"
#include "GameComponents/EnemyComponent.hpp"
#include "GameComponents/AlliedProjectileComponent.hpp"
#include "GameComponents/EnemyProjectileComponent.hpp"
#include "GameComponents/ObstacleComponent.hpp"
#include "GameSystems/CollidableSystem.hpp"

using namespace ecs;

Test(Collidable_Test, entities_does_not_collide)
{
    World world(1);

    std::size_t FirstId = world.addEntity().addComponent<Position>(10, 10).addComponent<Size>(15, 15).addComponent<Damage>(10).addComponent<Collidable>().addComponent<Enemy>().addComponent<Life>(20).getId();
    std::size_t SecondId = world.addEntity().addComponent<Position>(1000, 1000).addComponent<Size>(15, 15).addComponent<Damage>(10).addComponent<Collidable>().addComponent<Player>().addComponent<Life>(20).getId();

    world.addSystem<Collide>();

    Life fst = world.getEntity(FirstId).getComponent<Life>();
    Life snd = world.getEntity(SecondId).getComponent<Life>();

    cr_assert_eq(20, fst.lifePoint);
    cr_assert_eq(20, snd.lifePoint);
}