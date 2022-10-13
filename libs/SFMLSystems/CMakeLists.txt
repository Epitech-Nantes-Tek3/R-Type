set(INC_SFML_SYSTEM_ROOT ${PROJECT_SOURCE_DIR}/libs/SFMLSystems)

set(TARGET ${PROJECT_NAME}_SFMLSystems)

set(SRC
    ${INC_SFML_SYSTEM_ROOT}/InputManagement.cpp
    ${INC_SFML_SYSTEM_ROOT}/InputManagement.hpp
    ${INC_SFML_SYSTEM_ROOT}/DrawComponents.cpp
    ${INC_SFML_SYSTEM_ROOT}/DrawComponents.hpp
)

add_library(${TARGET} ${SRC})

target_include_directories(${TARGET}
    PUBLIC ${INC_SFML_SYSTEM_ROOT}
    PUBLIC ${PROJECT_NAME}_ecs
    PUBLIC ${PROJECT_NAME}_SFMLResource
)

target_link_libraries(${TARGET}
    ${PROJECT_NAME}_ecs
    ${PROJECT_NAME}_SFMLResource
    ${PROJECT_NAME}_SFMLComponents
)

set_target_properties(${TARGET} PROPERTIES LINKER_LANGUAGE CXX)