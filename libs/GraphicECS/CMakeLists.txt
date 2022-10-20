set(GRAPHIC_INC_ROOT ${PROJECT_SOURCE_DIR}/libs/GraphicECS)
set(GRAPHIC_SRC_COMPONENT_ROOT ${PROJECT_SOURCE_DIR}/libs/GraphicECS/SFMLComponents)
set(GRAPHIC_SRC_RESOURCE_ROOT ${PROJECT_SOURCE_DIR}/libs/GraphicECS/SFMLResource)
set(GRAPHIC_SRC_SYSTEM_ROOT ${PROJECT_SOURCE_DIR}/libs/GraphicECS/SFMLSystems)

set(TARGET ${PROJECT_NAME}_GraphicECS)

set(SRC

)

add_library(${TARGET} SHARED ${SRC})

target_include_directories(${TARGET}
    PUBLIC ${GRAPHIC_INC_ROOT}
    PRIVATE ${PROJECT_NAME}_ecs
    PRIVATE ${GRAPHIC_SRC_COMPONENT_ROOT}
    PRIVATE ${GRAPHIC_SRC_RESOURCE_ROOT}
    PRIVATE ${GRAPHIC_SRC_SYSTEM_ROOT}
)

target_link_libraries(${TARGET}
    ${PROJECT_NAME}_ecs
    CONAN_PKG::sfml
)

include(${PROJECT_SOURCE_DIR}/build/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)