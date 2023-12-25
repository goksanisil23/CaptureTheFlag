#pragma once

#include "../Components/Components.h"

class Agent
{
  public:
    static constexpr bool kDrawSensorRays{true};

    Agent(const raylib::Vector2 start_pos, const raylib::Color color, const float radius);
    void move();

    TransformComponent tf;
    RenderComponent    vis;
    RaySensorComponent sensor;

    bool has_sensor{true};
    bool has_flag{false};
};