set(INC_ROOT ${PROJECT_SOURCE_DIR}/libs/LibsClient/CreateEntitiesFunctions)

set(TARGET ${PROJECT_NAME}_createEntitiesFunctions)

set(SRC
    ${INC_ROOT}/CreateEnemyProjectile.hpp
    ${INC_ROOT}/CreateEnemyProjectile.cpp
    ${INC_ROOT}/CreateAlliedProjectile.hpp
    ${INC_ROOT}/CreateAlliedProjectile.cpp
    ${INC_ROOT}/CreatePlayer.hpp
    ${INC_ROOT}/CreateProjectile.hpp
)

add_library(${TARGET} SHARED ${SRC})

target_include_directories(${TARGET}
    PUBLIC ${INC_ROOT}
    PUBLIC ${PROJECT_NAME}_ecs
    INTERFACE ${PROJECT_NAME}_gameComponents
    INTERFACE ${PROJECT_NAME}_error
)

target_link_libraries(${TARGET}
    ${PROJECT_NAME}_gameComponents
    ${PROJECT_NAME}_ecs
)

set_target_properties(${TARGET} PROPERTIES LINKER_LANGUAGE CXX)