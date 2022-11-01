/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** Error
*/

#ifndef ERROR_HPP_
#define ERROR_HPP_

#include <exception>
#include <string>

namespace error_lib
{
    /// @brief Custom error class for rtype project
    class RTypeError : public std::exception {
      public:
        /// @brief Error basic constructor. Default value for component -> Unknow
        /// @param message The error message (Some description and information about the error)
        /// @param component Provenance of the error (File, function...)
        inline RTypeError(std::string const &message, std::string const &component = "Unknow")
            : _component(component), _message(message){};

        /// @brief Get the error information
        /// @return Error information in string format
        inline const char *what(void) const noexcept override { return _message.data(); };

        /// @brief Get the error provenance
        /// @return Error provenance in string format
        inline const std::string &getComponent(void) const noexcept { return _component; };

      protected:
      private:
        /// @brief Error information
        std::string const _component;

        /// @brief Error provenance
        std::string const _message;
    };

    /// @brief Error class for the network part
    class NetworkError : public RTypeError {
      public:
        /// @brief Constructor of the Network Error
        /// @param message Error message (Some description and information about the error)
        /// @param component Provenance of the error (File, function...)
        inline NetworkError(std::string const &message, std::string const &component = "Network")
            : RTypeError(message, component){};
    };

    /// @brief Error class for the ecs part
    class EcsError : public RTypeError {
      public:
        /// @brief Constructor of the Ecs Error
        /// @param message Error message (Some description and information about the error)
        /// @param component Provenance of the error (File, function...)
        inline EcsError(std::string const &message, std::string const &component = "Ecs")
            : RTypeError(message, component){};
    };

    /// @brief Error class for a malloc fail
    class MallocError : public RTypeError {
      public:
        /// @brief Constructor of the Malloc Error
        /// @param message Error message (Some description and information about the error)
        /// @param component Provenance of the error (File, function...)
        inline MallocError(std::string const &message, std::string const &component = "Malloc")
            : RTypeError(message, component){};
    };

    /// @brief Error class for a argument fail
    class ArgumentError : public RTypeError {
      public:
        /// @brief Constructor of the Argument Error
        /// @param message Error message (Some description and information about the error)
        /// @param component Provenance of the error (File, function...)
        inline ArgumentError(std::string const &message, std::string const &component = "ArgumentHandler")
            : RTypeError(message, component){};
    };

    /// @brief Error class for a signal detection
    class SignalError : public RTypeError {
      public:
        /// @brief Constructor of the Signal Error
        /// @param message Error message (Some description and information about the error)
        /// @param component Provenance of the error (File, function...)
        inline SignalError(std::string const &message, std::string const &component = "SignalThrowing")
            : RTypeError(message, component){};
    };
} // namespace error_lib

#endif /* !ERROR_HPP_ */
