set(SRC_ROOT ${PROJECT_SOURCE_DIR}/libs/ECS/Components)

set(SRC_COMPONENT
    ${SRC_ROOT}/Component.hpp
    ${SRC_ROOT}/SizeComponent.hpp
    ${SRC_ROOT}/PositionComponent.hpp
    ${SRC_ROOT}/ButtonComponent.hpp
    ${SRC_ROOT}/VelocityComponent.hpp
    ${SRC_ROOT}/MovementComponent.hpp
    ${SRC_ROOT}/ShootingFrequencyComponent.hpp
    PARENT_SCOPE
)
