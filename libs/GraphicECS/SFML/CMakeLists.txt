set(GRAPHIC_SRC_COMPONENT_ROOT ${PROJECT_SOURCE_DIR}/libs/GraphicECS/SFML/Components)
set(GRAPHIC_SRC_RESOURCE_ROOT ${PROJECT_SOURCE_DIR}/libs/GraphicECS/SFML/Resources)
set(GRAPHIC_SRC_SYSTEM_ROOT ${PROJECT_SOURCE_DIR}/libs/GraphicECS/SFML/Systems)
set(MACCRO_ROOT ${PROJECT_SOURCE_DIR}/include)

set(TARGET ${PROJECT_NAME}_SFMLGraphicECS)

add_subdirectory(Systems)
add_subdirectory(Components)
add_subdirectory(Resources)

set(SRC
    ${SRC_GRAPHIC_COMPONENT}
    ${SRC_GRAPHIC_RESOURCE}
    ${SRC_GRAPHIC_SYSTEM}
)

if (CMAKE_COMPILER_IS_GNUCXX)
    add_library(${TARGET} SHARED ${SRC})
elseif (MSVC)
   add_library(${TARGET} ${SRC})
else ()
  message(WARNING "Unknown compiler type, compilation may not work as expected")
endif()

target_include_directories(${TARGET}
    PUBLIC ${CONAN_INCLUDE_DIRS_SFML}
    PUBLIC ${GRAPHIC_SRC_COMPONENT_ROOT}
    PUBLIC ${GRAPHIC_SRC_RESOURCE_ROOT}
    PUBLIC ${GRAPHIC_SRC_SYSTEM_ROOT}
    PRIVATE ${PROJECT_NAME}_RTypeLogicGlobal
    PRIVATE ${PROJECT_NAME}_ecs
    PRIVATE ${MACCRO_ROOT}
)

target_link_libraries(${TARGET}
    ${PROJECT_NAME}_RTypeLogicGlobal
    ${PROJECT_NAME}_ecs
    ${PROJECT_NAME}_RTypeLogicButtonManipulation
    CONAN_PKG::sfml
)

include(${PROJECT_SOURCE_DIR}/build/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

install(TARGETS ${TARGET} DESTINATION bin)
