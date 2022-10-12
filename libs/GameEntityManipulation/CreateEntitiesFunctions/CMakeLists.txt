set(INC_ROOT ${PROJECT_SOURCE_DIR}/libs/GameEntityManipulation/CreateEntitiesFunctions)

set(TARGET ${PROJECT_NAME}_createEntitiesFunctions)

set(SRC
    ${INC_ROOT}/CreateEnemyProjectile.hpp
    ${INC_ROOT}/CreateAlliedProjectile.hpp
    ${INC_ROOT}/CreatePlayer.hpp
    ${INC_ROOT}/CreateProjectile.hpp
    ${INC_ROOT}/CreateEnemy.hpp
    ${INC_ROOT}/CreateEnemyRandomPosition.hpp
    ${INC_ROOT}/CreateObstacle.hpp
)

add_library(${TARGET} INTERFACE ${SRC})

set_target_properties(${TARGET} PROPERTIES LINKER_LANGUAGE CXX)