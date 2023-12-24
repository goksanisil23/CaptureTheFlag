#pragma once

#include "../Components/Components.h"

class Agent
{
  public:
    Agent();
    void move();

    PositionComponent pos;
    RenderComponent   vis;
};