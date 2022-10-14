set(INC_ROOT ${PROJECT_SOURCE_DIR}/libs/GameEntityManipulation/CreateEntitiesFunctions)

set(TARGET ${PROJECT_NAME}_createEntitiesFunctions)

set(SRC
    ${INC_ROOT}/CreateEnemyProjectile.hpp
    ${INC_ROOT}/CreateAlliedProjectile.hpp
    ${INC_ROOT}/CreatePlayer.hpp
    ${INC_ROOT}/CreateProjectile.hpp
    ${INC_ROOT}/CreateEnemy.hpp
    ${INC_ROOT}/CreateObstacle.hpp
    ${INC_ROOT}/CreateBackground.hpp
    ${INC_ROOT}/CreateButton.hpp
)

add_library(${TARGET} INTERFACE ${SRC})
