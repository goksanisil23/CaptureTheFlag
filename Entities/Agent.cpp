#include "Agent.h"

Agent::Agent(const raylib::Vector2 start_pos, const raylib::Color color, const float radius)
{
    tf.position = start_pos;
    vis.color   = color;
    vis.radius  = radius;

    sensor.ray_angles.clear();
    sensor.offset = vis.radius;
    sensor.ray_angles.push_back(-70.F);
    sensor.ray_angles.push_back(-30.F);
    sensor.ray_angles.push_back(0.F);
    sensor.ray_angles.push_back(30.F);
    sensor.ray_angles.push_back(70.F);
}

void Agent::move()
{
    tf.position.x += (float)rand() / RAND_MAX;
    tf.position.y += (float)rand() / RAND_MAX;
}