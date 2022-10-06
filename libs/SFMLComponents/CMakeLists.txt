set(SFML_INPUT_INC_ROOT ${PROJECT_SOURCE_DIR}/libs/SFMLComponents)

set(TARGET ${PROJECT_NAME}_SFMLComponents)

set(SRC
    ${SFML_INPUT_INC_ROOT}/AllowControllerComponent.hpp
    ${SFML_INPUT_INC_ROOT}/AllowMouseAndKeyboardComponent.hpp
    ${SFML_INPUT_INC_ROOT}/ControllerInputComponent.hpp
    ${SFML_INPUT_INC_ROOT}/KeyboardInputComponent.hpp
    ${SFML_INPUT_INC_ROOT}/MouseInputComponent.hpp
)

add_library(${TARGET} ${SRC})

target_include_directories(${TARGET}
    PUBLIC ${INC_ROOT}
)

target_link_libraries(${TARGET}
    ${PROJECT_NAME}_ecs
)

set_target_properties(${TARGET} PROPERTIES LINKER_LANGUAGE CXX)