set(SRC_ROOT ${PROJECT_SOURCE_DIR}/libs/GameSystems)
set(INC_ROOT ${PROJECT_SOURCE_DIR}/libs)

set(TARGET ${PROJECT_NAME}_gameSystems)

set(TARGET_CLIENT ${PROJECT_NAME}_clientSystems)

set(SRC
    ${SRC_ROOT}/MovementSystem.hpp
    ${SRC_ROOT}/DeathSystem.hpp
    ${SRC_ROOT}/DeathLifeSystem.hpp
    ${SRC_ROOT}/LifeTimeDeathSystem.hpp
    ${SRC_ROOT}/DecreaseLifeTimeSystem.hpp
    ${SRC_ROOT}/MovementSystem.cpp
    ${SRC_ROOT}/UpdateClockSystem.hpp
    ${SRC_ROOT}/UpdateClockSystem.cpp
    ${SRC_ROOT}/CollidableSystem.hpp
    ${SRC_ROOT}/CollidableSystem.cpp
)

add_library(${TARGET} SHARED ${SRC})

set(SRC_SYSTEM_CLIENT
    ${SRC_ROOT}/MovementSystem.cpp
    ${SRC_ROOT}/MovementSystem.hpp
    ${SRC_ROOT}/DeathSystem.hpp
)

add_library(${TARGET_CLIENT} SHARED ${SRC_SYSTEM_CLIENT})

target_include_directories(${TARGET}
    PUBLIC ${INC_ROOT}
    PRIVATE ${PROJECT_NAME}_ecs
    PRIVATE ${PROJECT_NAME}_gameComponents
    PRIVATE ${SRC_ROOT}
    PRIVATE ${PROJECT_NAME}_gameSharedResources
    PRIVATE ${SRC_ROOT}
)

target_include_directories(${TARGET_CLIENT}
    PUBLIC ${INC_ROOT}
    PRIVATE ${PROJECT_NAME}_ecs
    PRIVATE ${PROJECT_NAME}_gameComponents
    PRIVATE ${SRC_ROOT}
)

target_link_libraries(${TARGET}
    ${PROJECT_NAME}_ecs
    ${PROJECT_NAME}_gameComponents
    ${PROJECT_NAME}_gameSharedResources
)

target_link_libraries(${TARGET_CLIENT}
    ${PROJECT_NAME}_ecs
    ${PROJECT_NAME}_gameComponents
)
