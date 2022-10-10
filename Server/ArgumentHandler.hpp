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

namespace server_data
{
    /// @brief Class holding parse of arguments from main. Possibility of extract the data to create some other class
    class ArgumentHandler {
      public:

        /// @brief Construct a new ArgumentHandler object with default value
        ArgumentHandler();

        /// @brief Construct a new ArgumentHandler object
        /// @param ac Number of argument to parse
        /// @param av List of arguments to parse
        ArgumentHandler(const int ac, const char **av);

        /// @brief Destroy the Argument Handler object
        ~ArgumentHandler() = default;

      protected:
      private:
    };
} // namespace server_data

#endif /* !ARGUMENTHANDLER_HPP_ */
