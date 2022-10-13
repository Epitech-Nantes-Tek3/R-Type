add_subdirectory(Both)
add_subdirectory(Server)
add_subdirectory(Client)

set(SRC_TEL
    ${SRC_TEL_BOTH}
    ${SRC_TEL_SERVER}
    ${SRC_TEL_CLIENT}
    PARENT_SCOPE
)
