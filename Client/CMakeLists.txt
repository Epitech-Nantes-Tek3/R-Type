set(SRC_ROOT ${PROJECT_SOURCE_DIR}/Client)
set(INC_ROOT ${PROJECT_SOURCE_DIR}/Client)
set(MACCRO_ROOT ${PROJECT_SOURCE_DIR}/include)

set(TARGET r-type_client)

set(BUTTON_ACTION_SRC
    ${SRC_ROOT}/ButtonAction.hpp
    ${INC_ROOT}/ButtonAction.cpp
)

set(SRC
    ${SRC_ROOT}/main.cpp
    ${SRC_ROOT}/ClientRoom.cpp
    ${SRC_CLIENT_SYSTEM}
    ${SRC_ROOT}/ClientRoom.hpp
    ${SRC_ROOT}/UserConnection.cpp
    ${SRC_ROOT}/UserConnection.hpp
)

add_executable(${TARGET} ${SRC} ${BUTTON_ACTION_SRC})

set_property(TARGET ${TARGET} PROPERTY MSVC_RUNTIME_LIBRARY "")

set_target_properties(${TARGET}
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/
)

target_include_directories(${TARGET}
    PRIVATE ${MACCRO_ROOT}
)
target_link_libraries(${TARGET}
    ${PROJECT_NAME}_transisthor
    ${PROJECT_NAME}_argumentHandler
    ${PROJECT_NAME}_SFMLGraphicECS
    ${PROJECT_NAME}_RTypeLogicButtonManipulation
    ${PROJECT_NAME}_RTypeLogicRoom
)
