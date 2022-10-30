/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** SoundName
*/

#ifndef SOUNDNAME_HPP_
#define SOUNDNAME_HPP_

#include "Component/Component.hpp"
#include "GraphicECS/SFML/Resources/SoundResource.hpp"

namespace graphicECS::SFML::Components
{
    /// @brief SoundName stores the key as enum to the corresponding sound stored in shared resource SoundResource.
    class SoundName : public ecs::Component {
      public:
        /// @brief Enumeration of all status available for a Sound.
        /// Status STOPED specify that a sound is STOP but at it's begin
        enum status_e { STOPED, PAUSED, PLAYING };

        /// @brief The sound name stores an enum to find which sound it needs in SoundResources shared resource.
        graphicECS::SFML::Resources::SoundResource::soundName_e soundName;

        /// @brief Constructor of the SoundName component
        /// @param newSoundName The value to set in the soundName, corresponding
        /// on the sf::Sound load in shared resource Sound.
        SoundName(
            graphicECS::SFML::Resources::SoundResource::soundName_e newSoundName = graphicECS::SFML::Resources::SoundResource::UNDEFINED, status_e status = status_e::STOPED)
            : soundName(newSoundName), _status(status){};

        /// @brief Default destructor of SoundName component.
        ~SoundName() = default;

        /// @brief Status of the Sound
        status_e _status;
    };
} // namespace graphicECS::SFML::Components

#endif /* !SOUNDNAME_HPP_ */
