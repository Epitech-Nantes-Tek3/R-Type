set(GRAPHIC_SRC_COMPONENT_ROOT ${PROJECT_SOURCE_DIR}/libs/GraphicECS/SFMLComponents)
set(GRAPHIC_SRC_RESOURCE_ROOT ${PROJECT_SOURCE_DIR}/libs/GraphicECS/SFMLResource)
set(GRAPHIC_SRC_SYSTEM_ROOT ${PROJECT_SOURCE_DIR}/libs/GraphicECS/SFMLSystems)

set(TARGET ${PROJECT_NAME}_GraphicECS)

add_subdirectory(SFMLSystems)
add_subdirectory(SFMLComponents)
add_subdirectory(SFMLResource)

set(SRC
    ${SRC_GRAPHIC_COMPONENT}
    ${SRC_GRAPHIC_RESOURCE}
    ${SRC_GRAPHIC_SYSTEM}
)

add_library(${TARGET} SHARED ${SRC})

target_include_directories(${TARGET}
    PRIVATE ${CONAN_INCLUDE_DIRS_SFML}
    PUBLIC ${GRAPHIC_SRC_COMPONENT_ROOT}
    PUBLIC ${GRAPHIC_SRC_RESOURCE_ROOT}
    PUBLIC ${GRAPHIC_SRC_SYSTEM_ROOT}
    PRIVATE ${PROJECT_NAME}_ecs
)

target_link_libraries(${TARGET}
    ${PROJECT_NAME}_ecs
    CONAN_PKG::sfml
)

include(${PROJECT_SOURCE_DIR}/build/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)