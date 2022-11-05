set(SRC_RTYPE_LOGIC_ENTITY_CREATION_ROOT ${PROJECT_SOURCE_DIR}/libs/R-TypeLogic/EntityManipulation/CreateEntitiesFunctions)

set(TARGET ${PROJECT_NAME}_RTypeLogicCreateEntitiesFunctions)

set(SRC
    ${SRC_RTYPE_LOGIC_ENTITY_CREATION_ROOT}/CreateEnemyProjectile.hpp
    ${SRC_RTYPE_LOGIC_ENTITY_CREATION_ROOT}/CreateEnemyProjectile.cpp
    ${SRC_RTYPE_LOGIC_ENTITY_CREATION_ROOT}/CreateAlliedProjectile.hpp
    ${SRC_RTYPE_LOGIC_ENTITY_CREATION_ROOT}/CreateAlliedProjectile.cpp
    ${SRC_RTYPE_LOGIC_ENTITY_CREATION_ROOT}/CreatePlayer.hpp
    ${SRC_RTYPE_LOGIC_ENTITY_CREATION_ROOT}/CreatePlayer.cpp
    ${SRC_RTYPE_LOGIC_ENTITY_CREATION_ROOT}/CreateProjectile.hpp
    ${SRC_RTYPE_LOGIC_ENTITY_CREATION_ROOT}/CreateProjectile.cpp
    ${SRC_RTYPE_LOGIC_ENTITY_CREATION_ROOT}/CreateEnemy.hpp
    ${SRC_RTYPE_LOGIC_ENTITY_CREATION_ROOT}/CreateEnemy.cpp
    ${SRC_RTYPE_LOGIC_ENTITY_CREATION_ROOT}/CreateObstacle.hpp
    ${SRC_RTYPE_LOGIC_ENTITY_CREATION_ROOT}/CreateObstacle.cpp
    ${SRC_RTYPE_LOGIC_ENTITY_CREATION_ROOT}/CreateBackground.hpp
    ${SRC_RTYPE_LOGIC_ENTITY_CREATION_ROOT}/CreateBackground.cpp
    ${SRC_RTYPE_LOGIC_ENTITY_CREATION_ROOT}/CreateButton.hpp
    ${SRC_RTYPE_LOGIC_ENTITY_CREATION_ROOT}/CreateButton.cpp
    ${SRC_RTYPE_LOGIC_ENTITY_CREATION_ROOT}/CreateWritable.hpp
    ${SRC_RTYPE_LOGIC_ENTITY_CREATION_ROOT}/CreateWritable.cpp
    ${SRC_RTYPE_LOGIC_ENTITY_CREATION_ROOT}/CreateWritableButton.hpp
    ${SRC_RTYPE_LOGIC_ENTITY_CREATION_ROOT}/CreateWritableButton.cpp
    ${SRC_RTYPE_LOGIC_ENTITY_CREATION_ROOT}/CreateChatMessage.cpp
    ${SRC_RTYPE_LOGIC_ENTITY_CREATION_ROOT}/CreateChatMessage.hpp
)

add_library(${TARGET} ${SRC})

target_include_directories(${TARGET}
    PUBLIC ${SRC_RTYPE_LOGIC_ENTITY_CREATION_ROOT}
)

target_link_libraries(${TARGET}
    ${PROJECT_NAME}_transisthor
    ${PROJECT_NAME}_RTypeLogicButtonManipulation
)
