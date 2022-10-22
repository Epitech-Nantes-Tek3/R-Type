set(SRC_RType_Logic_SYSTEMS_ROOT ${PROJECT_SOURCE_DIR}/libs/R-TypeLogic/Server/Systems/)

set(SRC_RType_Logic_SERVER_SYSTEMS
    ${SRC_RType_Logic_SYSTEMS_ROOT}/DeathLifeSystem.hpp
    ${SRC_RType_Logic_SYSTEMS_ROOT}/LifeTimeDeathSystem.hpp
    ${SRC_RType_Logic_SYSTEMS_ROOT}/DecreaseLifeTimeSystem.hpp
    ${SRC_RType_Logic_SYSTEMS_ROOT}/CollidableSystem.hpp
    ${SRC_RType_Logic_SYSTEMS_ROOT}/CollidableSystem.cpp
    ${SRC_RType_Logic_SYSTEMS_ROOT}/EnemiesGoRandom.cpp
    ${SRC_RType_Logic_SYSTEMS_ROOT}/EnemiesGoRandom.hpp
    ${SRC_RType_Logic_SYSTEMS_ROOT}/EnemyShootSystem.cpp
    ${SRC_RType_Logic_SYSTEMS_ROOT}/EnemyShootSystem.hpp
    PARENT_SCOPE
)
