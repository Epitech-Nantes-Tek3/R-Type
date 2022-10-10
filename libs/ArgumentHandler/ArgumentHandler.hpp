/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** ArgumentHandler
*/

/// @file libs/ArgumentHandler/ArgumentHandler.hpp

#ifndef ARGUMENTHANDLER_HPP_
#define ARGUMENTHANDLER_HPP_

#include <string>
#include <vector>
#include <map>

namespace argument_handler
{
    /// @brief Class holding parse of arguments from main. Possibility of extract the data to create some other class
    class ArgumentHandler {
      public:

        /// @brief Struct containing all Arguments needs by the server executable
        struct ServerInformation {
            /// @brief Ip address to connect to.
            std::string address;

            /// @brief Port to bind to.
            unsigned short port;
        };

        /// @brief Struct containing all Arguments needs by the client executable
        struct ClientInformation {
           /// @brief Ip address to connect to.
            std::string clientAddress;

            /// @brief Port to bind to.
            unsigned short clientPort;

           /// @brief Server ip address to connect to.
            std::string serverAddress;

            /// @brief Server port to bind to.
            unsigned short serverPort;
        };

        /// @brief Type list of all the possible use of ArgumentHandler class
        enum ArgumentFunctionType {
            UNDEFINED,
            SERVER_EXECUTABLE,
            CLIENT_EXECUTABLE
        };

        /// @brief Construct a new ArgumentHandler object with default value
        ArgumentHandler();

        /// @brief Construct a new ArgumentHandler object
        /// @param ac Number of argument to parse
        /// @param av List of arguments to parse
        ArgumentHandler(const int ac, char **av);

        /// @brief Destroy the Argument Handler object
        ~ArgumentHandler() = default;

        /// @brief Bind all -h option text inside the _hTextList map
        void bindAllHOptionText(void);

        /// @brief Check if the passed arguments are a -h option. If is it, display matching -h
        /// @param functionType Matching Enum for the function type
        /// @return True if the passed arguments is a -h option.
        /// @return Otherwise, return false
        bool processHOptionVerification(ArgumentFunctionType functionType);

        /// @brief Extract all wanted value by server from stored arguments.
        /// @return A struct containing all wanted informations.
        ServerInformation extractServerInformation(void);

        /// @brief Extract all wanted value by client from stored arguments.
        /// @return A struct containing all wanted informations.
        ClientInformation extractClientInformation(void);

      private:

        /// @brief List of all the arguments to parse
        std::vector<std::string> _argumentsToParse;

        /// @brief List of all the -h option text
        std::map<unsigned short, std::string> _hTextList;
    };
} // namespace server_data

#endif /* !ARGUMENTHANDLER_HPP_ */
