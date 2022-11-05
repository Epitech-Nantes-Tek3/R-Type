add_subdirectory(Systems)

set(SRC_RTYPE_LOGIC_SYSTEMS_ROOT ${PROJECT_SOURCE_DIR}/libs/R-TypeLogic/Server)
set(INC_RTYPE_LOGIC_SYSTEMS_ROOT ${PROJECT_SOURCE_DIR}/libs/R-TypeLogic)

set(TARGET ${PROJECT_NAME}_RTypeLogicRoom)

if (CMAKE_COMPILER_IS_GNUCXX)
    add_library(${TARGET} SHARED ${SRC_RTYPE_LOGIC_SERVER_SYSTEMS})
elseif (MSVC)
   add_library(${TARGET} ${SRC_RTYPE_LOGIC_SERVER_SYSTEMS})
else ()
  message(WARNING "Unknown compiler type, compilation may not work as expected")
endif()


target_include_directories(${TARGET}
    PUBLIC ${INC_RTYPE_LOGIC_SYSTEMS_ROOT}
    PRIVATE ${PROJECT_NAME}_RTypeLogicGlobal
    PRIVATE ${SRC_RTYPE_LOGIC_SYSTEMS_ROOT}
)

target_link_libraries(${TARGET}
    ${PROJECT_NAME}_RTypeLogicGlobal
)
