add_subdirectory(Components)

add_library(ecs SHARED
    ${SRC_COMPONENT}
    )

target_include_directories(ecs PUBLIC ${SRC_COMPONENT})

set_target_properties(ecs PROPERTIES LINKER_LANGUAGE CXX)