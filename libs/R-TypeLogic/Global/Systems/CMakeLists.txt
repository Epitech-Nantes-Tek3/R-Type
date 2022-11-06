set(SRC_RTYPE_LOGIC_SYSTEMS_ROOT ${PROJECT_SOURCE_DIR}/libs/R-TypeLogic/Global/Systems)

set(SRC_RTYPE_LOGIC_GLOBAL_SYSTEMS
    ${SRC_RTYPE_LOGIC_SYSTEMS_ROOT}/MovementSystem.hpp
    ${SRC_RTYPE_LOGIC_SYSTEMS_ROOT}/DeathSystem.hpp
    ${SRC_RTYPE_LOGIC_SYSTEMS_ROOT}/MovementSystem.cpp
    ${SRC_RTYPE_LOGIC_SYSTEMS_ROOT}/UpdateClockSystem.hpp
    ${SRC_RTYPE_LOGIC_SYSTEMS_ROOT}/UpdateClockSystem.cpp
    ${SRC_RTYPE_LOGIC_SYSTEMS_ROOT}/NoAfkInMenuSystem.hpp
    ${SRC_RTYPE_LOGIC_SYSTEMS_ROOT}/NoAfkInMenuSystem.cpp
    ${SRC_RTYPE_LOGIC_SYSTEMS_ROOT}/ElectricInvisibleEnemySystem.cpp
    ${SRC_RTYPE_LOGIC_SYSTEMS_ROOT}/ElectricInvisibleEnemySystem.hpp
    PARENT_SCOPE
)
