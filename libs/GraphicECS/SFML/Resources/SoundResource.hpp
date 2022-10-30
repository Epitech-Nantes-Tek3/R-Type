/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** SoundResources
*/

#ifndef SOUNDRESOURCES_HPP_
#define SOUNDRESOURCES_HPP_

#include <SFML/Audio.hpp>
#include <filesystem>
#include "Resource/Resource.hpp"
#include <unordered_map>

namespace graphicECS::SFML::Resources
{
    /// @brief This resource class stores a map of Sounds SFML.
    class SoundResource : public ecs::Resource {
      public:
        /// @brief Enumeration of all available Sounds
        enum soundName_e { UNDEFINED, SHOOT, DEATH, EXPLOSION };

        /// @brief Name of map which contains Sounds.
        using SoundsList = std::unordered_map<soundName_e, std::shared_ptr<sf::Sound>>;

        /// @brief Add a Sound from it's Sound Path passed as parameter
        /// @param sound_e Enum of the Sound
        /// @param soundPath The sound path to be used.
        inline SoundResource(const soundName_e sound_e, const std::filesystem::path &soundPath)
        {
            addSound(sound_e, soundPath);
        }

        /// @brief Add a sound to the SoundsList
        /// @param sound_e Enum which give the name of the Sound
        /// @param soundPath Path of the Sound
        void addSound(const soundName_e sound_e, const std::filesystem::path &soundPath);

        /// @brief Default destructor
        ~SoundResource() = default;

        SoundsList _soundsList;
    };
} // namespace ecs

#endif /* !SOUNDRESOURCES_HPP_ */
