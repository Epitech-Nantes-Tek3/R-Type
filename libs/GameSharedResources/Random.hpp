/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** Random
*/

#ifndef RANDOM_HPP_
#define RANDOM_HPP_

#include <random>
#include "Resource/Resource.hpp"

namespace ecs
{
    /// Random Shared Resource.
    struct RandomDevice : public Resource {
      public:
        /// Construct a new Random Device Shared Resource
        RandomDevice() : _generation(_device()) {}

        /// @brief Generate a random number in the interval [min, max]
        /// @tparam numeric type of the numbers.
        /// @param min minimum value.
        /// @param max maximum value.
        /// @return numeric value in the interval [min, max]
        template <typename numeric> numeric randInt(numeric min, numeric max)
        {
            std::uniform_int_distribution<std::mt19937::result_type> dist(min, max);

            return dist(_generation);
        }

      private:
        /// @brief Will be used to obtain a seed for the random number engine
        std::random_device _device;
        /// @brief Standard generation seeded with rd()
        std::mt19937 _generation;
    };
} // namespace game::resources

#endif /* !RANDOM_HPP_ */
