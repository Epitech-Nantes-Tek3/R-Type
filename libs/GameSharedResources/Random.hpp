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
    /// Game map resource.
    struct RandomDevice : public Resource {
      public:
        /// Construct a new Random Device resource
        RandomDevice() : _generation(_device()) {}

        /// Generate a random number in the interval [min, max]
        ///
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
        std::random_device _device;
        std::mt19937 _generation;
    };
} // namespace game::resources

#endif /* !RANDOM_HPP_ */
