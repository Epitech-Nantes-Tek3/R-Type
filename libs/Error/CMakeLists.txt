set(INC_ROOT ${PROJECT_SOURCE_DIR}/libs)
set(SRC_ROOT ${PROJECT_SOURCE_DIR}/libs/Error)

set(TARGET ${PROJECT_NAME}_error)

set(SRC
    ${SRC_ROOT}/Error.cpp

    ${SRC_ROOT}/Error.hpp
)

add_library(${TARGET} ${SRC})

target_include_directories(${TARGET}
    PUBLIC ${INC_ROOT}
    PRIVATE ${SRC_ROOT}
)
