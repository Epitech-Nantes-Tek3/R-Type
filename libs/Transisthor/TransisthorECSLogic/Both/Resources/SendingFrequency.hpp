/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** SendingFrequency
*/

#pragma once

#include <chrono>
#include "Resource/Resource.hpp"

class SendingFrequency : public ecs::Resource {
  public:
    /// @brief Construct a new Sending Frequency object
    SendingFrequency();

    /// @brief Destroy the Sending Frequency object
    ~SendingFrequency(){};

    /// @brief Check if the system can send informations
    /// @return bool True if the system can send informations
    bool canBeRunNew();
    /// @brief Check if the system can send informations
    /// @return bool True if the system can send informations
    bool canBeRunUpdate();

    /// @brief Reset the time point of the last send of the system which send new entities
    void resetNewClock();
    /// @brief Reset the time point of the last send of the system which send updated components
    void resetUpdateClock();

  private:
    /// @brief The time point of the last send of the system which send new entities
    std::chrono::steady_clock::time_point _lastTimeNew;
    /// @brief The time point of the last send of the system which send updated components
    std::chrono::steady_clock::time_point _lastTimeUpdate;

    /// @brief the frenquency value
    std::chrono::duration<double> _frequency;
};
