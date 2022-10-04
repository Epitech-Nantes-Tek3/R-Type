set(SRC_ROOT ${PROJECT_SOURCE_DIR}/libs/ECS/Components)

set(SRC_COMPONENT
    ${SRC_ROOT}/Component.hpp
    ${SRC_ROOT}/SizeComponent.hpp
    ${SRC_ROOT}/PositionComponent.hpp
    ${SRC_ROOT}/ButtonComponent.hpp
    ${SRC_ROOT}/VelocityComponent.hpp
    ${SRC_ROOT}/MovementComponent.hpp
    ${SRC_ROOT}/ShootingFrequencyComponent.hpp
    ${SRC_ROOT}/ControlableComponent.hpp
    ${SRC_ROOT}/LifeComponent.hpp
    ${SRC_ROOT}/DamageComponent.hpp
    ${SRC_ROOT}/LifetimeComponent.hpp
    ${SRC_ROOT}/EquipableComponent.hpp
    ${SRC_ROOT}/WeaknessComponent.hpp
    ${SRC_ROOT}/CollidableComponent.hpp
    ${SRC_ROOT}/HitboxSizeComponent.hpp
    ${SRC_ROOT}/BreakthroughtComponent.hpp
    ${SRC_ROOT}/BouncingComponent.hpp
    ${SRC_ROOT}/DamageRadiusComponent.hpp
    ${SRC_ROOT}/WeightComponent.hpp
    ${SRC_ROOT}/InvisibleComponent.hpp
    ${SRC_ROOT}/InvinsibleComponent.hpp
    PARENT_SCOPE
)
