set(SRC_TEL_CLIENT_SYSTEM_ROOT ${PROJECT_SOURCE_DIR}/libs/Transisthor/ECSLogic/Client/Systems)

set(SRC_TEL_CLIENT_SYSTEM
    ${SRC_TEL_CLIENT_SYSTEM_ROOT}/SendToServer.hpp
    ${SRC_TEL_CLIENT_SYSTEM_ROOT}/SendToServer.cpp
    ${SRC_TEL_CLIENT_SYSTEM_ROOT}/SendNewlyCreatedToServer.hpp
    ${SRC_TEL_CLIENT_SYSTEM_ROOT}/SendNewlyCreatedToServer.cpp
    PARENT_SCOPE
)
