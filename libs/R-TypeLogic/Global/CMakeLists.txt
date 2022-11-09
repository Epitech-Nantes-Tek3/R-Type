add_subdirectory(Components)
add_subdirectory(SharedResources)
add_subdirectory(Systems)

set(TARGET ${PROJECT_NAME}_RTypeLogicGlobal)

add_library(${TARGET}
    ${SRC_RTYPE_LOGIC_COMPONENTS}
    ${SRC_RTYPE_LOGIC_RESOURCES}
    ${SRC_RTYPE_LOGIC_GLOBAL_SYSTEMS}
)

target_include_directories(${TARGET}
    PRIVATE ${PROJECT_NAME}_ecs
)

target_link_libraries(${TARGET}
    ${PROJECT_NAME}_ecs
    ${PROJECT_NAME}_RTypeLogicCreateEntitiesFunctions
)

install(TARGETS ${TARGET} DESTINATION lib)