set(SRC_RL_SYSTEMS_ROOT ${PROJECT_SOURCE_DIR}/libs/R-TypeLogic/Systems)
set(INC_RL_SYSTEMS_ROOT ${PROJECT_SOURCE_DIR}/libs/R-TypeLogic)

############################################
# Create the Global R-Type Systems Library #
############################################
set (SRC_RL_GLOBAL_SYSTEMS
    ${SRC_RL_SYSTEMS_ROOT}/MovementSystem.hpp
    ${SRC_RL_SYSTEMS_ROOT}/DeathSystem.hpp
    ${SRC_RL_SYSTEMS_ROOT}/MovementSystem.cpp
    PARENT_SCOPE
)

############################################
# Create the Server R-Type Systems Library #
############################################
set(TARGET_SERVER ${PROJECT_NAME}_RTypeServerSystems)

set(SRC_RL_SERVER_SYSTEMS
    ${SRC_RL_SYSTEMS_ROOT}/DeathLifeSystem.hpp
    ${SRC_RL_SYSTEMS_ROOT}/LifeTimeDeathSystem.hpp
    ${SRC_RL_SYSTEMS_ROOT}/DecreaseLifeTimeSystem.hpp
    ${SRC_RL_SYSTEMS_ROOT}/UpdateClockSystem.hpp
    ${SRC_RL_SYSTEMS_ROOT}/UpdateClockSystem.cpp
    ${SRC_RL_SYSTEMS_ROOT}/CollidableSystem.hpp
    ${SRC_RL_SYSTEMS_ROOT}/CollidableSystem.cpp
    ${SRC_RL_SYSTEMS_ROOT}/EnemiesGoRandom.cpp
    ${SRC_RL_SYSTEMS_ROOT}/EnemiesGoRandom.hpp
    ${SRC_RL_SYSTEMS_ROOT}/EnemyShootSystem.cpp
    ${SRC_RL_SYSTEMS_ROOT}/EnemyShootSystem.hpp
)

add_library(${TARGET_SERVER} SHARED ${SRC_RL_SERVER_SYSTEMS})

target_include_directories(${TARGET_SERVER}
    PUBLIC ${INC_RL_SYSTEMS_ROOT}
    PRIVATE ${PROJECT_NAME}_rl
    PRIVATE ${SRC_RL_SYSTEMS_ROOT}
)

target_link_libraries(${TARGET_SERVER}
    ${PROJECT_NAME}_rl
)
