add_subdirectory(Components)
add_subdirectory(Systems)

set(SRC_TEL_SERVER
    ${SRC_TEL_SERVER_SYSTEM}
    ${SRC_TEL_SERVER_COMP}
PARENT_SCOPE)
