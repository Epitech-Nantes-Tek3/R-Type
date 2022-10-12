set(SFML_INPUT_INC_ROOT ${PROJECT_SOURCE_DIR}/libs/SFMLComponents)

set(TARGET ${PROJECT_NAME}_SFMLComponents)

set(SRC
    ${SFML_INPUT_INC_ROOT}/AllowControllerComponent.hpp
    ${SFML_INPUT_INC_ROOT}/AllowMouseAndKeyboardComponent.hpp
    ${SFML_INPUT_INC_ROOT}/ControllerButtonInputComponent.hpp
    ${SFML_INPUT_INC_ROOT}/ControllerJoystickInputComponent.hpp
    ${SFML_INPUT_INC_ROOT}/KeyboardInputComponent.hpp
    ${SFML_INPUT_INC_ROOT}/MouseInputComponent.hpp
    ${SFML_INPUT_INC_ROOT}/ECSActions.hpp
)

add_library(${TARGET} SHARED ${SRC})

target_include_directories(${TARGET}
    PUBLIC ${SFML_INPUT_INC_ROOT}
    PRIVATE ${PROJECT_NAME}_ecs
)

target_link_libraries(${TARGET}
    ${PROJECT_NAME}_ecs
)

include(${PROJECT_SOURCE_DIR}/build/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)