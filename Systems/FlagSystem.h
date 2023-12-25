#pragma once

#include "Typedefs.h"
#include "raylib-cpp.hpp"

#include "../Entities/Agent.h"

class FlagSystem
{
  public:
    FlagSystem();

    void step(std::vector<Agent> &agents);

  private:
    raylib::Vector2 position;
};