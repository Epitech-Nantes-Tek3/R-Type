/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** GlobalScore
*/

#ifndef GLOBALSCORE_HPP_
#define GLOBALSCORE_HPP_

#include "Resource/Resource.hpp"

namespace ecs
{
    /// @brief Shared resource Score. When an enemy is killed, the score is updated.
    /// The added points depend on the type of enemy killed.
    class GlobalScore : public Resource {
      public:
        /// @brief Create the Global Score, initializing the score to 0
        GlobalScore() : _score(0){};

        /// @brief It updates the score, corresponding to the enemy type
        /// @param enemyType the type of the killed enemy
        void updateScore(unsigned int enemyType);

        /// @brief Default Destructor
        ~GlobalScore() = default;

      private:
        /// @brief the score who will be updated, and send to database at the end of the room
        unsigned int _score;
    };
} // namespace ecs

#endif /* !GLOBALSCORE_HPP_ */
