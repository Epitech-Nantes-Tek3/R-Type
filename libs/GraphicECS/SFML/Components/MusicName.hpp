/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** MusicName
*/

#ifndef MUSICNAME_HPP_
#define MUSICNAME_HPP_

#include "Component/Component.hpp"
#include "GraphicECS/SFML/Resources/MusicResource.hpp"

namespace graphicECS::SFML::Components
{
    /// @brief MusicName stores the key as enum to the corresponding music stored in shared resource MusicResource.
    class MusicName : public Component {
      public:

        /// @brief Enumeration of all status available for a Music.
        /// Status STOPED specify that a music is STOP but at it's begin
        enum status_e { STOPED, PAUSED, PLAYING };

        /// @brief The music name stores an enum to find which music it needs in MusicResources shared resource
        MusicResource::musicName_e musicName;

        /// @brief Constructor of the MusicName component
        /// @param newMusicName The value to set in the musicName, corresponding
        /// on the sf::Music load in shared resource Music.
        MusicName(MusicResource::musicName_e newMusicName = MusicResource::UNDEFINED, status_e status = status_e::STOPED)
            : musicName(newMusicName), _status(status) {};

        /// @brief Default destructor of MusicName component.
        ~MusicName() = default;

        /// @brief This function return the status of the Music
        inline status_e getStatus() const { return _status; };

        /// @brief This function set the status of the Music
        inline void setStatus(status_e status) { _status = status; };

        /// @brief This function return the name of the Music
        inline MusicResource::musicName_e getName() const { return musicName; };

        /// @brief This function set the name of the Music
        inline void setName(MusicResource::musicName_e name) { musicName = name; };
      private:
        status_e _status;
    };
} // namespace graphicECS::SFML::Components

#endif /* !MUSICNAME_HPP_ */
