set(GRAPHIC_SRC_COMPONENT_ROOT ${PROJECT_SOURCE_DIR}/libs/GraphicECS/SFML/Components)

set(SRC_GRAPHIC_COMPONENT
    ${GRAPHIC_SRC_COMPONENT_ROOT}/AllowControllerComponent.hpp
    ${GRAPHIC_SRC_COMPONENT_ROOT}/AllowMouseAndKeyboardComponent.hpp
    ${GRAPHIC_SRC_COMPONENT_ROOT}/ControllerButtonInputComponent.hpp
    ${GRAPHIC_SRC_COMPONENT_ROOT}/ControllerJoystickInputComponent.hpp
    ${GRAPHIC_SRC_COMPONENT_ROOT}/KeyboardInputComponent.hpp
    ${GRAPHIC_SRC_COMPONENT_ROOT}/MouseInputComponent.hpp
    ${GRAPHIC_SRC_COMPONENT_ROOT}/ECSActions.hpp
    ${GRAPHIC_SRC_COMPONENT_ROOT}/GraphicsRectangleComponent.hpp
    ${GRAPHIC_SRC_COMPONENT_ROOT}/GraphicsRectangleComponent.cpp
    ${GRAPHIC_SRC_COMPONENT_ROOT}/GraphicsTextComponent.hpp
    ${GRAPHIC_SRC_COMPONENT_ROOT}/GraphicsTextComponent.cpp
    ${GRAPHIC_SRC_COMPONENT_ROOT}/TextureName.hpp
    ${GRAPHIC_SRC_COMPONENT_ROOT}/ParallaxComponent.hpp
    PARENT_SCOPE
)
