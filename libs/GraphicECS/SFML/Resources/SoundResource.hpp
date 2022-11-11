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
        enum sound_e { UNDEFINED, SHOOT, DEATH, EXPLOSION };

        /// @brief Name of map which contains Sounds.
        using SoundsList = std::unordered_map<sound_e, std::shared_ptr<sf::SoundBuffer>>;

        /// @brief Default Constructor of SoundResource.
        SoundResource() : playSound(true){};

        /// @brief Add a Sound from its Sound Path passed as parameter
        /// @param sound_e Enum of the Sound
        /// @param soundPath The sound path to be used.
        inline SoundResource(const sound_e sound_e, const std::filesystem::path &soundPath)
        {
            addSound(sound_e, soundPath);
        }

        /// @brief Add a sound to the SoundsList
        /// @param sound_e Enum which give the name of the Sound
        /// @param soundPath Path of the Sound
        void addSound(const sound_e sound_e, const std::filesystem::path &soundPath);

        /// @brief Default destructor
        ~SoundResource() = default;

        /// @brief The map which contains Sounds
        SoundsList _soundsList;

        bool playSound;
    };
} // namespace graphicECS::SFML::Resources

#endif /* !SOUNDRESOURCES_HPP_ */
