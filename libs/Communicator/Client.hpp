/*
** EPITECH PROJECT, 2022
** Project
** File description:
** client
*/

/// @file libs/Communicator/Client.hpp

#ifndef CLIENT_HPP_
#define CLIENT_HPP_

#include <string>

namespace communicator_lib
{
    /// @brief A representation of a client (Address + Port)
    class Client
    {
    public:
        /// @brief Construct a new Client object
        /// @param address The address of the client
        /// @param port The port of the client
        Client(std::string address = "127.0.0.1", long port = 0);

        /// @brief Destroy the Client object
        ~Client();

        /// @brief Get the Address value
        /// @return std::string A reference to the address value
        std::string getAddress(void) const;

        /// @brief Get the Port value
        /// @return long The value of the port
        long getPort(void) const;

        /// @brief Set the Address value
        /// @param address The newly address
        void setAddress(std::string address);

        /// @brief Set the Port value
        /// @param port The new port number
        void setPort(long port);

    private:
        /// @brief The ip address of the client (127.0.0.1 by default)
        std::string _address;
        /// @brief The port of the client (0 by default)
        long _port;
    };

    /// @brief Overload of the == operator to compare to client
    /// @param left The left param of the comparison
    /// @param right The right param of the comparison
    /// @return true If the two client are the same
    /// @return false If the two client are different
    inline bool operator==(const Client &left, const Client &right)
    {
        return ((left.getPort() == right.getPort()) && (left.getAddress() == right.getAddress()));
    }
};

#endif /* !CLIENT_HPP_ */
