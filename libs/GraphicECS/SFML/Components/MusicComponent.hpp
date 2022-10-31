/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** MusicComponent
*/

#ifndef MUSICNAME_HPP_
#define MUSICNAME_HPP_

#include "Component/Component.hpp"
#include "GraphicECS/SFML/Resources/MusicResource.hpp"

using namespace graphicECS::SFML::Resources;

namespace graphicECS::SFML::Components
{
    /// @brief MusicComponent stores the key as enum to the corresponding music stored in shared resource
    /// MusicResource.
    class MusicComponent : public ecs::Component {
      public:
        /// @brief Enumeration of all status available for a Music.
        /// Status STOPED specify that a music is STOP but at it's begin
        enum status_e { STOPED, PAUSED, PLAYING };

        /// @brief The music name stores an enum to find which music it needs in MusicResources shared resource
        MusicResource::music_e musicName;

        /// @brief Constructor of the MusicComponent component
        /// @param newMusicComponent The value to set in the musicName, corresponding
        /// on the sf::Music load in shared resource Music.
        MusicComponent(
            MusicResource::music_e newMusicComponent = MusicResource::UNDEFINED, status_e status = status_e::STOPED)
            : musicName(newMusicComponent), _status(status){};

        /// @brief Default destructor of MusicComponent component.
        ~MusicComponent() = default;

        /// @brief  Status of the Music
        status_e _status;
    };
} // namespace graphicECS::SFML::Components

#endif /* !MUSICNAME_HPP_ */
