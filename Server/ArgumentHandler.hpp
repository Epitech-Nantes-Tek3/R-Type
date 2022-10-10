/*
** EPITECH PROJECT, 2022
** Project
** File description:
** ArgumentHandler
*/

/// @file Server/ArgumentHandler.hpp

#ifndef ARGUMENTHANDLER_HPP_
#define ARGUMENTHANDLER_HPP_

#include <string>
#include <vector>
#include <map>

namespace server_data
{
    /// @brief Class holding parse of arguments from main. Possibility of extract the data to create some other class
    class ArgumentHandler {
      public:

        /// @brief Struct containing all Argument needs by the server executable
        struct ServerInformation {
            /// @brief Ip address to connect to.
            std::string address;

            /// @brief Port to bind to.
            unsigned short port;
        };

        /// @brief Type list of all the possible use of ArgumentHandler class
        enum ArgumentFunctionType {
            UNDEFINED,
            SERVER_EXECUTABLE
        };

        /// @brief Construct a new ArgumentHandler object with default value
        ArgumentHandler();

        /// @brief Construct a new ArgumentHandler object
        /// @param ac Number of argument to parse
        /// @param av List of arguments to parse
        ArgumentHandler(const int ac, const char **av);

        /// @brief Destroy the Argument Handler object
        ~ArgumentHandler() = default;

        /// @brief Bind all -h option text inside the _hTextList map
        void bindAllHOptionText(void);

        /// @brief Extract all wanted value by server from stored arguments.
        /// @return A struct containing all wanted informations.
        ServerInformation extractServerInformation(void);

      private:

        /// @brief List of all the arguments to parse
        std::vector<std::string> _argumentsToParse;

        /// @brief List of all the -h option text
        std::map<unsigned short, std::string> _hTextList;
    };
} // namespace server_data

#endif /* !ARGUMENTHANDLER_HPP_ */
