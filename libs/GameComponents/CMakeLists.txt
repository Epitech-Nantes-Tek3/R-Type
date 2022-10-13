set(INC_ROOT ${PROJECT_SOURCE_DIR}/libs/GameComponents)

set(TARGET ${PROJECT_NAME}_gameComponents)

set(SRC
    ${INC_ROOT}/SizeComponent.hpp
    ${INC_ROOT}/PositionComponent.hpp
    ${INC_ROOT}/ButtonComponent.hpp
    ${INC_ROOT}/VelocityComponent.hpp
    ${INC_ROOT}/DestinationComponent.hpp
    ${INC_ROOT}/ShootingFrequencyComponent.hpp
    ${INC_ROOT}/ControlableComponent.hpp
    ${INC_ROOT}/LifeComponent.hpp
    ${INC_ROOT}/DamageComponent.hpp
    ${INC_ROOT}/LifeTimeComponent.hpp
    ${INC_ROOT}/EquipmentComponent.hpp
    ${INC_ROOT}/WeaknessComponent.hpp
    ${INC_ROOT}/CollidableComponent.hpp
    ${INC_ROOT}/BreakThroughtComponent.hpp
    ${INC_ROOT}/BouncingComponent.hpp
    ${INC_ROOT}/DamageRadiusComponent.hpp
    ${INC_ROOT}/WeightComponent.hpp
    ${INC_ROOT}/InvisibleComponent.hpp
    ${INC_ROOT}/InvinsibleComponent.hpp
    ${INC_ROOT}/DeathDamageComponent.hpp
    ${INC_ROOT}/PatternComponent.hpp
    ${INC_ROOT}/ChargedAttackComponent.hpp
    ${INC_ROOT}/DeathComponent.hpp
    ${INC_ROOT}/AlliedProjectileComponent.hpp
    ${INC_ROOT}/EnemyProjectileComponent.hpp
    ${INC_ROOT}/ProjectileComponent.hpp
    ${INC_ROOT}/PlayerComponent.hpp
    ${INC_ROOT}/EnemyComponent.hpp
    ${INC_ROOT}/ObstacleComponent.hpp
)

add_library(${TARGET} INTERFACE ${SRC})

