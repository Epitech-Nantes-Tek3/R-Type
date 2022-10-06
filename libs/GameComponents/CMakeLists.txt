<<<<<<< HEAD
set(SRC_ROOT ${PROJECT_SOURCE_DIR}/libs/GameComponents)
=======
set(INC_ROOT ${PROJECT_SOURCE_DIR}/libs/GameComponents)
>>>>>>> 8dc919d (Fix games components #66)

set(TARGET ${PROJECT_NAME}_gameComponents)

set(SRC
<<<<<<< HEAD
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
=======
    ${INC_ROOT}/SizeComponent.hpp
    ${INC_ROOT}/PositionComponent.hpp
    ${INC_ROOT}/ButtonComponent.hpp
    ${INC_ROOT}/VelocityComponent.hpp
    ${INC_ROOT}/DestinationComponent.hpp
    ${INC_ROOT}/ShootingFrequencyComponent.hpp
    ${INC_ROOT}/ControlableComponent.hpp
    ${INC_ROOT}/LifeComponent.hpp
    ${INC_ROOT}/DamageComponent.hpp
    ${INC_ROOT}/LifetimeComponent.hpp
    ${INC_ROOT}/EquipableComponent.hpp
    ${INC_ROOT}/WeaknessComponent.hpp
    ${INC_ROOT}/CollidableComponent.hpp
    ${INC_ROOT}/BreakthroughtComponent.hpp
    ${INC_ROOT}/BouncingComponent.hpp
    ${INC_ROOT}/DamageRadiusComponent.hpp
    ${INC_ROOT}/WeightComponent.hpp
    ${INC_ROOT}/InvisibleComponent.hpp
    ${INC_ROOT}/InvinsibleComponent.hpp
    ${INC_ROOT}/DeathDamageComponent.hpp
    ${INC_ROOT}/PatternComponent.hpp
    ${INC_ROOT}/ChargedAttackComponent.hpp
    ${INC_ROOT}/test.cpp
>>>>>>> 8dc919d (Fix games components #66)
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