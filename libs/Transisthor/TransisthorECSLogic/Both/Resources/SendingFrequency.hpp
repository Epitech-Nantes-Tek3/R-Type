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
    SendingFrequency();
    ~SendingFrequency(){};
    bool canBeRunNew();
    bool canBeRunUpdate();

  private:
    std::chrono::steady_clock::time_point _lastTimeNew;
    std::chrono::steady_clock::time_point _lastTimeUpdate;

    std::chrono::duration<double> _frequency;
};
