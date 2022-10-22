set(SRC_RL_SYSTEMS_ROOT ${PROJECT_SOURCE_DIR}/libs/R-TypeLogic/Global/Systems/)
set(INC_RL_SYSTEMS_ROOT ${PROJECT_SOURCE_DIR}/libs/R-TypeLogic)

set(SRC_RL_GLOBAL_SYSTEMS
    ${SRC_RL_SYSTEMS_ROOT}/MovementSystem.hpp
    ${SRC_RL_SYSTEMS_ROOT}/DeathSystem.hpp
    ${SRC_RL_SYSTEMS_ROOT}/MovementSystem.cpp
    ${SRC_RL_SYSTEMS_ROOT}/UpdateClockSystem.hpp
    ${SRC_RL_SYSTEMS_ROOT}/UpdateClockSystem.cpp
    PARENT_SCOPE
)
