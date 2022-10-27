/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** MusicName
*/

#ifndef MUSICNAME_HPP_
#define MUSICNAME_HPP_

#include "Component/Component.hpp"
#include "GraphicECS/SFML/Resources/SoundResource.hpp"

namespace ecs
{
    /// @brief MusicName store the key as enum to the corresponding music stores in shared resource SoundResource.
    class MusicName : public Component {
      public:
        /// @brief Enumeration of all status available for a Music.
        /// Status BEGIN specify that a music is STOP but at it's begin
        enum status_e { BEGIN, STOP, PLAYING };

        /// @brief The music name stores to find the corresponding musicName.
        SoundResource::musicName_e musicName;

        /// @brief Constructor of the MusicName component
        /// @param newMusicName The value to set in the musicName, corresponding
        /// on the sf::Sound load in shared resource Sound.
        MusicName(SoundResource::musicName_e newMusicName = SoundResource::UNDEFINED, status_e status = status_e::BEGIN)
            : musicName(newMusicName){};

        /// @brief Default destructor of MusicName component.
        ~MusicName() = default;

      private:
        status_e _status;
    };
} // namespace ecs

#endif /* !MUSICNAME_HPP_ */
