/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** SoundComponent
*/

#ifndef SOUNDCOMPONENT_HPP_
#define SOUNDCOMPONENT_HPP_

#include "Component/Component.hpp"
#include "GraphicECS/SFML/Resources/SoundResource.hpp"

using namespace graphicECS::SFML::Resources;

namespace graphicECS::SFML::Components
{
    /// @brief SoundComponent stores the key as enum to the corresponding sound stored in shared resource
    /// SoundResource.
    class SoundComponent : public ecs::Component {
      public:
        /// @brief Enumeration of all status available for a Sound.
        /// Status STOPED specify that a sound is STOP but at it's begin
        enum status_e { STOPED, PAUSED, PLAYING };

        /// @brief The sound stores an enum to find which sound it needs in SoundResources shared resource
        SoundResource::sound_e sound_e;

        /// @brief Constructor of the SoundComponent component
        /// @param newSoundComponent The value to set in the sound_e, corresponding
        /// on the sf::Sound load in shared resource Sound.
        SoundComponent(
            SoundResource::sound_e newSoundComponent = SoundResource::UNDEFINED, status_e status = status_e::STOPED)
            : sound_e(newSoundComponent), _status(status){};

        /// @brief Default destructor of SoundComponent component.
        ~SoundComponent() = default;

        /// @brief Status of the Sound
        status_e _status;
    };
} // namespace graphicECS::SFML::Components

#endif /* !SOUNDCOMPONENT_HPP_ */
