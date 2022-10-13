set(INC_SFML_SYSTEM_ROOT ${PROJECT_SOURCE_DIR}/libs/SFMLSystems)

set(TARGET ${PROJECT_NAME}_SFMLSystems)

set(SRC
    ${INC_SFML_SYSTEM_ROOT}/InputManagement.cpp
    ${INC_SFML_SYSTEM_ROOT}/InputManagement.hpp
)

add_library(${TARGET} ${SRC})

set_target_properties(${TARGET} PROPERTIES LINKER_LANGUAGE CXX)