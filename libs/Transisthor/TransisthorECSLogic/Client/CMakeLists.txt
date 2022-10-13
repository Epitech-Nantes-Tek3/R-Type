add_subdirectory(Components)
add_subdirectory(Systems)

set(SRC_TEL_CLIENT ${SRC_TEL_CLIENT_COMP} ${SRC_TEL_CLIENT_SYSTEM} PARENT_SCOPE)
