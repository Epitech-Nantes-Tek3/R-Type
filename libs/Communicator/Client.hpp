/*
** EPITECH PROJECT, 2022
** Project
** File description:
** client
*/

/// \file libs/Communicator/Client.hpp

#ifndef CLIENT_HPP_
    #define CLIENT_HPP_

    #include <string>

namespace communicator_lib {
    class Client {
        public:
            Client(std::string address = "127.0.0.1", long port = 0);
            ~Client();
            std::string getAddress(void);
            long getPort(void);
            void setAddress(std::string address);
            void setPort(long port);

        protected:

        private:
            /// \brief The ip address of the client (127.0.0.1 by default)
            std::string address;
            /// \brief The port of the client (0 by default)
            long port;
    };
};

#endif /* !CLIENT_HPP_ */
