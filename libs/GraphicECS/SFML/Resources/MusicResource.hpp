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

namespace ecs
{
    /// @brief This resource class stores a map of Musics SFML.
    class MusicResource : public Resource {
      public:
        /// @brief Enumeration of all available Musics
        enum musicName_e { UNDEFINED, SHOOT, DEATH, EXPLOSION };

        /// @brief Name of map which contains Musics.
        using MusicsList = std::unordered_map<musicName_e, std::shared_ptr<sf::Music>>;

        /// @brief Add a Music from it's Music Path passed as parameter
        /// @param music_e Enum of the Music
        /// @param musicPath The music path to be used.
        inline MusicResource(const musicName_e music_e, const std::filesystem::path &musicPath)
        {
            addMusic(music_e, musicPath);
        }

        /// @brief Add a music to the MusicsList
        /// @param music_e Enum which give the name of the Music
        /// @param musicPath Path of the Music
        void addMusic(const musicName_e music_e, const std::filesystem::path &musicPath);

        /// @brief Default destructor
        ~MusicResource() = default;

        MusicsList _musicsList;
    };
} // namespace ecs

#endif /* !MUSICRESOURCE_HPP_ */
