set(GRAPHIC_SRC_COMPONENT_ROOT ${PROJECT_SOURCE_DIR}/libs/GraphicECS/SFML/Components)
set(GRAPHIC_SRC_RESOURCE_ROOT ${PROJECT_SOURCE_DIR}/libs/GraphicECS/SFML/Resources)
set(GRAPHIC_SRC_SYSTEM_ROOT ${PROJECT_SOURCE_DIR}/libs/GraphicECS/SFML/Systems)

set(TARGET ${PROJECT_NAME}_SFMLGraphicECS)

add_subdirectory(Systems)
add_subdirectory(Components)
add_subdirectory(Resources)

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
    PRIVATE ${PROJECT_NAME}_gameSharedResources
    PRIVATE ${PROJECT_NAME}_ecs
)

target_link_libraries(${TARGET}
    ${PROJECT_NAME}_gameSharedResources
    ${PROJECT_NAME}_ecs
    CONAN_PKG::sfml
)

include(${PROJECT_SOURCE_DIR}/build/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)