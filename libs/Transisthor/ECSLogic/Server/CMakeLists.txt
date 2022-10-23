add_subdirectory(Components)
add_subdirectory(Systems)
add_subdirectory(Resources)

set(SRC_TEL_SERVER
    ${SRC_TEL_SERVER_SYSTEM}
    ${SRC_TEL_SERVER_COMP}
    ${SRC_TEL_SERVER_RESOURCES}
PARENT_SCOPE)
