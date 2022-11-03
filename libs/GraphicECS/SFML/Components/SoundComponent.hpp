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
        /// @brief The sound stores an enum to find which sound it needs in SoundResources shared resource
        SoundResource::sound_e sound_e;

        /// @brief Constructor of the SoundComponent component
        /// @param newSoundComponent The value to set in the sound_e, corresponding
        /// @param status The status of the song STOPED by default
        /// on the sf::Sound load in shared resource Sound.
        SoundComponent(SoundResource::sound_e newSoundComponent = SoundResource::UNDEFINED,
            sf::SoundSource::Status status = sf::SoundSource::Status::Stopped)
            : sound_e(newSoundComponent), _status(status){};

        /// @brief Default destructor of SoundComponent component.
        ~SoundComponent() = default;

        /// @brief Status of the Sound
        sf::SoundSource::Status _status;
    };
} // namespace graphicECS::SFML::Components

#endif /* !SOUNDCOMPONENT_HPP_ */
