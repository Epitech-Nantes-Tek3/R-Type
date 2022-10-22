set(SRC_RType_Logic_SYSTEMS_ROOT ${PROJECT_SOURCE_DIR}/libs/R-TypeLogic/Global/Systems/)
set(INC_RType_Logic_SYSTEMS_ROOT ${PROJECT_SOURCE_DIR}/libs/R-TypeLogic)

set(SRC_RType_Logic_GLOBAL_SYSTEMS
    ${SRC_RType_Logic_SYSTEMS_ROOT}/MovementSystem.hpp
    ${SRC_RType_Logic_SYSTEMS_ROOT}/DeathSystem.hpp
    ${SRC_RType_Logic_SYSTEMS_ROOT}/MovementSystem.cpp
    ${SRC_RType_Logic_SYSTEMS_ROOT}/UpdateClockSystem.hpp
    ${SRC_RType_Logic_SYSTEMS_ROOT}/UpdateClockSystem.cpp
    PARENT_SCOPE
)
