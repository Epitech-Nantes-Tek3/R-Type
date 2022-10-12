set(SRC_ROOT ${PROJECT_SOURCE_DIR}/libs/GameSystems)
set(INC_ROOT ${PROJECT_SOURCE_DIR}/libs)

set(TARGET ${PROJECT_NAME}_gameSystems)

set(SRC
    ${SRC_ROOT}/MouvementSystem.hpp
)

add_library(${TARGET} SHARED ${SRC})

target_include_directories(${TARGET}
    PUBLIC ${INC_ROOT}
    PRIVATE ${PROJECT_NAME}_ecs
    PRIVATE ${PROJECT_NAME}_gameComponents
    PRIVATE ${SRC_ROOT}
)

target_link_libraries(${TARGET}
    ${PROJECT_NAME}_ecs
    ${PROJECT_NAME}_gameComponents
)
