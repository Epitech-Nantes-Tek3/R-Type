set(INC_SFML_SYSTEM_ROOT ${PROJECT_SOURCE_DIR}/libs/SFMLSystems)

set(TARGET ${PROJECT_NAME}_SFMLSystems)

set(SRC
    ${INC_SFML_SYSTEM_ROOT}/InputManagement.cpp
    ${INC_SFML_SYSTEM_ROOT}/InputManagement.hpp
    ${INC_SFML_SYSTEM_ROOT}/DrawComponents.cpp
    ${INC_SFML_SYSTEM_ROOT}/DrawComponents.hpp
    ${INC_SFML_SYSTEM_ROOT}/SfRectangleFollowEntitySystem.cpp
    ${INC_SFML_SYSTEM_ROOT}/SfRectangleFollowEntitySystem.hpp
    ${INC_SFML_SYSTEM_ROOT}/ParallaxSystem.cpp
    ${INC_SFML_SYSTEM_ROOT}/ParallaxSystem.hpp
)

add_library(${TARGET} SHARED ${SRC})

target_include_directories(${TARGET}
    PUBLIC ${INC_SFML_SYSTEM_ROOT}
    PRIVATE ${PROJECT_NAME}_ecs
    INTERFACE ${PROJECT_NAME}_SFMLResource
)

target_link_libraries(${TARGET}
    ${PROJECT_NAME}_ecs
    ${PROJECT_NAME}_SFMLResource
    ${PROJECT_NAME}_SFMLComponents
)
