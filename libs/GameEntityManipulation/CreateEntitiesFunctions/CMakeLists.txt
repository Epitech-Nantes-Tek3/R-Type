set(INC_ROOT ${PROJECT_SOURCE_DIR}/libs/GameEntityManipulation/CreateEntitiesFunctions)

set(TARGET ${PROJECT_NAME}_createEntitiesFunctions)

set(SRC
    ${INC_ROOT}/CreateAlliedProjectile.hpp
    ${INC_ROOT}/CreateAlliedProjectile.cpp
    ${INC_ROOT}/CreateBackground.hpp
    ${INC_ROOT}/CreateBackground.cpp
    ${INC_ROOT}/CreateButton.hpp
    ${INC_ROOT}/CreateButton.cpp
    ${INC_ROOT}/CreateEnemy.hpp
    ${INC_ROOT}/CreateEnemy.cpp
    ${INC_ROOT}/CreateEnemyProjectile.hpp
    ${INC_ROOT}/CreateEnemyProjectile.cpp
    ${INC_ROOT}/CreatePlayer.hpp
    ${INC_ROOT}/CreateProjectile.hpp
    ${INC_ROOT}/CreateObstacle.hpp
)

add_library(${TARGET} SHARED ${SRC})
