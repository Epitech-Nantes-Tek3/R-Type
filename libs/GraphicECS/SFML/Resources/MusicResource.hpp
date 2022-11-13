/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** MusicResource
*/

#ifndef MUSICRESOURCE_HPP_
#define MUSICRESOURCE_HPP_

#include <SFML/Audio.hpp>
#include <filesystem>
#include "Resource/Resource.hpp"
#include <unordered_map>

namespace graphicECS::SFML::Resources
{
    /// @brief This resource class stores a map of Musics SFML.
    class MusicResource : public ecs::Resource {
      public:
        /// @brief Enumeration of all available Musics
        enum music_e { UNDEFINED, MENUTHEME, LEVEL_ONE_THEME, LEVEL_TWO_THEME, LEVEL_THREE_THEME, LEVEL_FOUR_THEME, BOSS_FIGHTTHEME, INFINITE_THEME };

        /// @brief Name of map which contains Musics.
        using MusicsList = std::unordered_map<music_e, std::shared_ptr<sf::Music>>;

        /// @brief Constructor of MusicResource.
        MusicResource() : playMusic(true){};

        /// @brief Constructor to add a Music from its Music Path passed as parameter
        /// @param music_e Enum of the Music
        /// @param musicPath The music path to be used.
        inline MusicResource(const music_e music_e, const std::filesystem::path &musicPath)
        {
            addMusic(music_e, musicPath);
        }

        /// @brief Add a music to the MusicsList
        /// @param music_e Enum which gives the name of the Music
        /// @param musicPath Path of the Music
        void addMusic(const music_e music_e, const std::filesystem::path &musicPath);

        /// @brief Default destructor
        ~MusicResource() = default;

        /// @brief The Map which countains Musics
        MusicsList _musicsList;

        /// @brief A boolean which is used to know if the music is playing or not.
        bool playMusic;
    };
} // namespace graphicECS::SFML::Resources

#endif /* !MUSICRESOURCE_HPP_ */
