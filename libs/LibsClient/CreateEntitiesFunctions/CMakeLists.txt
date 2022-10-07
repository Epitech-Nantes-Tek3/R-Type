set(INC_ROOT ${PROJECT_SOURCE_DIR}/libs/LibsClient/CreateEntitiesFunctions)

set(TARGET ${PROJECT_NAME}_createEntitiesFunctions)

set(SRC
    ${INC_ROOT}/CreateEnemyProjectile.hpp
)

add_library(${TARGET} ${SRC})

target_include_directories(${TARGET}
    PUBLIC ${INC_ROOT}
    INTERFACE ${PROJECT_NAME}_error
)

target_link_libraries(${TARGET}
    ${PROJECT_NAME}_gameComponents
)

set_target_properties(${TARGET} PROPERTIES LINKER_LANGUAGE CXX)