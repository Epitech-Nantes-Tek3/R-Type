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

Test(Toto, tata)
{
    cr_assert_eq(42, 42);
}