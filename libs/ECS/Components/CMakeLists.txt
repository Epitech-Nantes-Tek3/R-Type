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
    PARENT_SCOPE
)
