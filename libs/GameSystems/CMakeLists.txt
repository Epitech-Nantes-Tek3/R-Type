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
)

set(SRC_SYSTEM_CLIENT
    ${SRC_ROOT}/MovementSystem.hpp
    ${SRC_ROOT}/DeathSystem.hpp
)

add_library(${TARGET} ${SRC})

add_library(${TARGET_CLIENT} ${SRC_SYSTEM_CLIENT})

target_include_directories(${TARGET}
    PUBLIC ${INC_ROOT}
    PUBLIC ${PROJECT_NAME}_ecs
    PUBLIC ${PROJECT_NAME}_gameComponents
    INTERFACE ${PROJECT_NAME}_error
    PRIVATE $(SRC_ROOT)
)

target_include_directories(${TARGET_CLIENT}
    PUBLIC ${INC_ROOT}
    PUBLIC ${PROJECT_NAME}_ecs
    PUBLIC ${PROJECT_NAME}_gameComponents
    INTERFACE ${PROJECT_NAME}_error
    PRIVATE $(SRC_ROOT)
)

target_link_libraries(${TARGET}
    ${PROJECT_NAME}_ecs
    ${PROJECT_NAME}_gameComponents
)

target_link_libraries(${TARGET_CLIENT}
    ${PROJECT_NAME}_ecs
    ${PROJECT_NAME}_gameComponents
)


set_target_properties(${TARGET} PROPERTIES LINKER_LANGUAGE CXX)

set_target_properties(${TARGET_CLIENT} PROPERTIES LINKER_LANGUAGE CXX)