set(INC_ROOT ${PROJECT_SOURCE_DIR}/libs)
set(SRC_ROOT ${PROJECT_SOURCE_DIR}/libs/Transisthor)

set(TARGET ${PROJECT_NAME}_transisthor)

set(SRC
    ${SRC_ROOT}/Transisthor.cpp

    ${SRC_ROOT}/Transisthor.hpp
)

add_library(${TARGET} ${SRC})

target_include_directories(${TARGET}
    PUBLIC ${INC_ROOT}
    PUBLIC ${PROJECT_NAME}_communicator
    PUBLIC ${PROJECT_NAME}_ecs
    PUBLIC ${PROJECT_NAME}_gameComponents
    INTERFACE ${PROJECT_NAME}_error
    PRIVATE ${SRC_ROOT}
)

target_link_libraries(${TARGET}
    ${PROJECT_NAME}_error
    ${PROJECT_NAME}_communicator
    ${PROJECT_NAME}_ecs
    ${PROJECT_NAME}_gameComponents
)