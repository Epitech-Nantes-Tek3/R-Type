/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** MusicComponent
*/

#ifndef MUSICCOMPONENT_HPP_
#define MUSICCOMPONENT_HPP_

#include "Component/Component.hpp"
#include "GraphicECS/SFML/Resources/MusicResource.hpp"

using namespace graphicECS::SFML::Resources;

namespace graphicECS::SFML::Components
{
    /// @brief MusicComponent stores the key as enum to the corresponding music stored in shared resource MusicResource.
    class MusicComponent : public ecs::Component {
      public:
        /// @brief The music stores an enum to find which music it needs in MusicResources shared resource
        MusicResource::music_e music_e;

        /// @brief Constructor of the MusicComponent component
        /// @param newMusicComponent The value to set in the music_e, corresponding
        /// @param status The status of the Music, STOPED by defaut
        /// on the sf::Music load in shared resource Music.
        MusicComponent(MusicResource::music_e newMusicComponent = MusicResource::UNDEFINED,
            sf::SoundSource::Status status = sf::SoundSource::Status::Stopped)
            : music_e(newMusicComponent), _status(status){};

        /// @brief Default destructor of MusicComponent component.
        ~MusicComponent() = default;

        /// @brief Status of the Music
        sf::SoundSource::Status _status;
    };
} // namespace graphicECS::SFML::Components

#endif /* !MUSICCOMPONENT_HPP_ */
