#include "Agent.h"

Agent::Agent()
{
    pos.position = raylib::Vector2{100, 100};
    vis.color    = raylib::Color::Yellow();
}

void Agent::move()
{
    pos.position.x += 0.1;
    pos.position.y += 0.2;
}