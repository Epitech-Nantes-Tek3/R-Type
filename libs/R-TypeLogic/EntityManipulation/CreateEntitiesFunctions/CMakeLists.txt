set(SRC_RL_ENTITY_CREATION_ROOT ${PROJECT_SOURCE_DIR}/libs/R-TypeLogic/EntityManipulation/CreateEntitiesFunctions)

set(TARGET ${PROJECT_NAME}_RTypeLogicCreateEntitiesFunctions)

set(SRC
    ${SRC_RL_ENTITY_CREATION_ROOT}/CreateEnemyProjectile.hpp
    ${SRC_RL_ENTITY_CREATION_ROOT}/CreateAlliedProjectile.hpp
    ${SRC_RL_ENTITY_CREATION_ROOT}/CreatePlayer.hpp
    ${SRC_RL_ENTITY_CREATION_ROOT}/CreateProjectile.hpp
    ${SRC_RL_ENTITY_CREATION_ROOT}/CreateEnemy.hpp
    ${SRC_RL_ENTITY_CREATION_ROOT}/CreateObstacle.hpp
    ${SRC_RL_ENTITY_CREATION_ROOT}/CreateBackground.hpp
    ${SRC_RL_ENTITY_CREATION_ROOT}/CreateButton.hpp
)

add_library(${TARGET} INTERFACE ${SRC})
