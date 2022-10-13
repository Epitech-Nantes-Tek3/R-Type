set(INC_SFML_RESOURCE_ROOT ${PROJECT_SOURCE_DIR}/libs/SFMLResource)

set(TARGET ${PROJECT_NAME}_SFMLResource)

set(SRC
    ${INC_SFML_RESOURCE_ROOT}/RenderWindowResource.hpp
    ${INC_SFML_RESOURCE_ROOT}/GraphicsFontResource.hpp
    ${INC_SFML_RESOURCE_ROOT}/GraphicsTextureResource.hpp
)

add_library(${TARGET} SHARED ${SRC})

target_include_directories(${TARGET}
    PUBLIC ${INC_SFML_RESOURCE_ROOT}
    PRIVATE ${PROJECT_NAME}_ecs
)

target_link_libraries(${TARGET}
    ${PROJECT_NAME}_ecs
    CONAN_PKG::sfml
)

include(${PROJECT_SOURCE_DIR}/build/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)