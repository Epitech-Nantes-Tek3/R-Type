set(GRAPHIC_SRC_SYSTEM_ROOT ${PROJECT_SOURCE_DIR}/libs/GraphicECS/SFML/Systems)

set(SRC_GRAPHIC_SYSTEM
    ${GRAPHIC_SRC_SYSTEM_ROOT}/InputManagement.cpp
    ${GRAPHIC_SRC_SYSTEM_ROOT}/InputManagement.hpp
    ${GRAPHIC_SRC_SYSTEM_ROOT}/DrawComponents.cpp
    ${GRAPHIC_SRC_SYSTEM_ROOT}/DrawComponents.hpp
    ${GRAPHIC_SRC_SYSTEM_ROOT}/SfRectangleFollowEntitySystem.cpp
    ${GRAPHIC_SRC_SYSTEM_ROOT}/SfRectangleFollowEntitySystem.hpp
    ${GRAPHIC_SRC_SYSTEM_ROOT}/ParallaxSystem.cpp
    ${GRAPHIC_SRC_SYSTEM_ROOT}/ParallaxSystem.hpp
    PARENT_SCOPE
)
