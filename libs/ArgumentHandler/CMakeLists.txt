set(INC_ROOT ${PROJECT_SOURCE_DIR}/libs)
set(SRC_ROOT ${PROJECT_SOURCE_DIR}/libs/ArgumentHandler)

set(TARGET ${PROJECT_NAME}_argumentHandler)

set(SRC
    ${SRC_ROOT}/ArgumentHandler.cpp

    ${SRC_ROOT}/ArgumentHandler.hpp
)

add_library(${TARGET} SHARED ${SRC})

target_include_directories(${TARGET}
    PUBLIC ${INC_ROOT}
    INTERFACE ${PROJECT_NAME}_error
    PRIVATE ${SRC_ROOT}
)

target_link_libraries(${TARGET}
    ${PROJECT_NAME}_error
)
