set(INC_ROOT ${PROJECT_SOURCE_DIR}/libs)
set(SRC_ROOT ${PROJECT_SOURCE_DIR}/libs/Error)

set(TARGET ${PROJECT_NAME}_error)

set(SRC
    ${SRC_ROOT}/Error.hpp
)

add_library(${TARGET} INTERFACE ${SRC})

install(TARGETS ${TARGET} DESTINATION bin)