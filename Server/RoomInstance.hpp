/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** RoomInstance
*/

#pragma once

#include <boost/process.hpp>
#include "Communicator/Client.hpp"

namespace serverData
{
    /// @brief A class that represents a room instance.
    class RoomInstance {
      public:
        /// @brief It creates a new room instance
        /// @param id The id of the room.
        /// @param name The name of the room.
        /// @param address The address of the server.
        /// @param port the port on which the room will listen to
        RoomInstance(unsigned short id, std::string name, std::string address, unsigned short port);

        /// @brief The destructor for the RoomInstance class
        /// It waits that the process is stoped
        ~RoomInstance();

        /// @brief It returns the Id of the room.
        /// @return The Id of the room
        inline unsigned short getId() const { return _id; }

        /// @brief It returns the name of the room.
        /// @return The name of the room
        inline std::string getName() const { return _name; }

        /// @brief It returns the network informations of the client
        /// @return The network informations.
        inline communicator_lib::Client getNetworkInfos() const { return _networkInformations; }

        /// @brief It returns a reference to the input stream of the process
        /// @return The input stream of the process
        inline boost::process::opstream &getInputStream() { return *_input; }

        /// @brief It returns a reference to the output stream of the process
        /// @return The output stream of the process
        inline boost::process::ipstream &getOutputStream() { return *_output; }

        /// @brief If the child process is running, terminate it.
        inline void terminate() { _child->terminate(); }

        /// @brief It waits for the process to finish
        inline void wait() { _child->wait(); }

      private:
        /// @brief Id of the room
        unsigned short _id;

        /// @brief Name of the room
        std::string _name;

        /// @brief Network informations of the room
        communicator_lib::Client _networkInformations;

        /// @brief The input stream of the process
        boost::process::opstream *_input;

        /// @brief The output stream of the process
        boost::process::ipstream *_output;

        /// @brief The child process which is running the room
        boost::process::child *_child;
    };

    /// @brief Overload of the == operator to compare two rooms
    /// @param left param of the comparison
    /// @param right param of the comparison
    /// @return true If the two rooms have the same id
    /// @return false If the two rooms have different id
    inline bool operator==(const RoomInstance &left, const RoomInstance &right)
    {
        return (left.getId() == right.getId());
    }

    /// @brief Overload of the == operator to compare rooms with her id
    /// @param left param of the comparison
    /// @param right param of the comparison
    /// @return true If the two rooms have the same id
    /// @return false If the two rooms have different id
    inline bool operator==(const RoomInstance &left, const unsigned short &right) { return (left.getId() == right); }

    /// @brief Overload of the == operator to compare rooms with her name
    /// @param left param of the comparison
    /// @param right param of the comparison
    /// @return true If the room have the good name
    /// @return false If the room haven't the good name
    inline bool operator==(const RoomInstance &left, const std::string &right) { return (left.getName() == right); }

} // namespace serverData
