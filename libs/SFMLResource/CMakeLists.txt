set(INC_SFML_RESOURCE_ROOT ${PROJECT_SOURCE_DIR}/libs/SFMLResource)

set(TARGET ${PROJECT_NAME}_SFMLResource)

set(SRC
    ${INC_SFML_RESOURCE_ROOT}/RenderWindowResource.hpp
)

add_library(${TARGET} INTERFACE ${SRC})

set_target_properties(${TARGET} PROPERTIES LINKER_LANGUAGE CXX)