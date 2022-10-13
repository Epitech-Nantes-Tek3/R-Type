set(SRC_ROOT ${PROJECT_SOURCE_DIR}/libs/GameSharedResources)
set(INC_ROOT ${PROJECT_SOURCE_DIR}/libs)

set(TARGET ${PROJECT_NAME}_gameSharedResources)

set(SRC
    ${SRC_ROOT}/GameClock.cpp
    ${SRC_ROOT}/GameClock.hpp
)

add_library(${TARGET} ${SRC})

target_include_directories(${TARGET}
    PUBLIC ${INC_ROOT}
    PUBLIC ${PROJECT_NAME}_ecs
)

target_link_libraries(${TARGET}
    ${PROJECT_NAME}_ecs
)

set_target_properties(${TARGET} PROPERTIES LINKER_LANGUAGE CXX)