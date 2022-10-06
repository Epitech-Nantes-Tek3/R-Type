set(SRC_ROOT ${PROJECT_SOURCE_DIR}/libs/GameSystems)
set(INC_ROOT ${PROJECT_SOURCE_DIR}/libs)

set(TARGET ${PROJECT_NAME}_gameSystems)

set(SRC
    ${SRC_ROOT}/MouvementSystem.hpp
)

add_library(${TARGET} ${SRC})

target_include_directories(${TARGET}
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

set_target_properties(${TARGET} PROPERTIES LINKER_LANGUAGE CXX)