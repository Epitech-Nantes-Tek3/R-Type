set(SRC_TEL_SERVER_SYSTEM_ROOT ${PROJECT_SOURCE_DIR}/libs/Transisthor/ECSLogic/Server/Systems)

set(SRC_TEL_SERVER_SYSTEM
    ${SRC_TEL_SERVER_SYSTEM_ROOT}/SendToClient.hpp
    ${SRC_TEL_SERVER_SYSTEM_ROOT}/SendToClient.cpp
    ${SRC_TEL_SERVER_SYSTEM_ROOT}/SendNewlyCreatedToClients.hpp
    ${SRC_TEL_SERVER_SYSTEM_ROOT}/SendNewlyCreatedToClients.cpp
    PARENT_SCOPE
)
