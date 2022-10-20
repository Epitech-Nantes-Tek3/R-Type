set(GRAPHIC_SRC_RESOURCE_ROOT ${PROJECT_SOURCE_DIR}/libs/GraphicECS/SFMLResource)

set(SRC_GRAPHIC_RESOURCE
    ${GRAPHIC_SRC_RESOURCE_ROOT}/RenderWindowResource.hpp
    ${GRAPHIC_SRC_RESOURCE_ROOT}/GraphicsFontResource.hpp
    ${GRAPHIC_SRC_RESOURCE_ROOT}/GraphicsTextureResource.hpp
    ${GRAPHIC_SRC_RESOURCE_ROOT}/GraphicsTextureResource.cpp
    PARENT_SCOPE
)
