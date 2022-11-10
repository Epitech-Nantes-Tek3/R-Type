set(GRAPHIC_SRC_SYSTEM_ROOT ${PROJECT_SOURCE_DIR}/libs/GraphicECS/SFML/Systems)

set(SRC_GRAPHIC_SYSTEM
    ${GRAPHIC_SRC_SYSTEM_ROOT}/InputManagement.cpp
    ${GRAPHIC_SRC_SYSTEM_ROOT}/InputManagement.hpp
    ${GRAPHIC_SRC_SYSTEM_ROOT}/DrawComponents.cpp
    ${GRAPHIC_SRC_SYSTEM_ROOT}/DrawComponents.hpp
    ${GRAPHIC_SRC_SYSTEM_ROOT}/SfObjectFollowEntitySystem.cpp
    ${GRAPHIC_SRC_SYSTEM_ROOT}/SfObjectFollowEntitySystem.hpp
    ${GRAPHIC_SRC_SYSTEM_ROOT}/ParallaxSystem.cpp
    ${GRAPHIC_SRC_SYSTEM_ROOT}/ParallaxSystem.hpp
    ${GRAPHIC_SRC_SYSTEM_ROOT}/SoundManagement.cpp
    ${GRAPHIC_SRC_SYSTEM_ROOT}/SoundManagement.hpp
    ${GRAPHIC_SRC_SYSTEM_ROOT}/MusicManagement.cpp
    ${GRAPHIC_SRC_SYSTEM_ROOT}/MusicManagement.hpp
    ${GRAPHIC_SRC_SYSTEM_ROOT}/AnimationSystem.cpp
    ${GRAPHIC_SRC_SYSTEM_ROOT}/AnimationSystem.hpp
    ${GRAPHIC_SRC_SYSTEM_ROOT}/RemoveChatSystem.cpp
    ${GRAPHIC_SRC_SYSTEM_ROOT}/RemoveChatSystem.hpp
    ${GRAPHIC_SRC_SYSTEM_ROOT}/UpdateParallaxSystem.cpp
    ${GRAPHIC_SRC_SYSTEM_ROOT}/UpdateParallaxSystem.hpp
    ${GRAPHIC_SRC_SYSTEM_ROOT}/ApplyInputDelay.cpp
    ${GRAPHIC_SRC_SYSTEM_ROOT}/ApplyInputDelay.hpp
    PARENT_SCOPE
)
