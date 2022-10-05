set(SRC_ROOT ${PROJECT_SOURCE_DIR}/libs/GameComponents)

set(TARGET ${PROJECT_NAME}_gameComponents)

set(SRC
    ${SRC_ROOT}/SizeComponent.hpp
    ${SRC_ROOT}/PositionComponent.hpp
    ${SRC_ROOT}/ButtonComponent.hpp
    ${SRC_ROOT}/VelocityComponent.hpp
    ${SRC_ROOT}/DestinationComponent.hpp
    ${SRC_ROOT}/ShootingFrequencyComponent.hpp
    ${SRC_ROOT}/ControlableComponent.hpp
    ${SRC_ROOT}/LifeComponent.hpp
    ${SRC_ROOT}/DamageComponent.hpp
    ${SRC_ROOT}/LifetimeComponent.hpp
    ${SRC_ROOT}/EquipableComponent.hpp
    ${SRC_ROOT}/WeaknessComponent.hpp
    ${SRC_ROOT}/CollidableComponent.hpp
    ${SRC_ROOT}/BreakthroughtComponent.hpp
    ${SRC_ROOT}/BouncingComponent.hpp
    ${SRC_ROOT}/DamageRadiusComponent.hpp
    ${SRC_ROOT}/WeightComponent.hpp
    ${SRC_ROOT}/InvisibleComponent.hpp
    ${SRC_ROOT}/InvinsibleComponent.hpp
    ${SRC_ROOT}/DeathDamageComponent.hpp
    ${SRC_ROOT}/PatternComponent.hpp
    ${SRC_ROOT}/ChargedAttackComponent.hpp
)

add_library(${TARGET} ${SRC})

target_include_directories(${TARGET}
    PUBLIC ${INC_ROOT}
    INTERFACE ${PROJECT_NAME}_error
)

target_link_libraries(${TARGET}
    ${PROJECT_NAME}_ecs
)

set_target_properties(${TARGET} PROPERTIES LINKER_LANGUAGE CXX)