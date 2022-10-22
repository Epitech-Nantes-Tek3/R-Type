add_subdirectory(Systems)

set(SRC_RL_SYSTEMS_ROOT ${PROJECT_SOURCE_DIR}/libs/R-TypeLogic/Server/)
set(INC_RL_SYSTEMS_ROOT ${PROJECT_SOURCE_DIR}/libs/R-TypeLogic)

set(TARGET ${PROJECT_NAME}_RTypeLogicServer)

add_library(${TARGET}
    SHARED
    ${SRC_RL_SERVER_SYSTEMS}
)

target_include_directories(${TARGET}
    PUBLIC ${INC_RL_SYSTEMS_ROOT}
    PRIVATE ${PROJECT_NAME}_RTypeLogicGlobal
    PRIVATE ${SRC_RL_SYSTEMS_ROOT}
)

target_link_libraries(${TARGET}
    ${PROJECT_NAME}_RTypeLogicGlobal
)
