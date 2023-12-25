#pragma once

#include "raylib-cpp.hpp"

#include "Typedefs.h"

struct TransformComponent
{
    raylib::Vector2 position;
    float           rotation;
};

struct RenderComponent
{
    // raylib::Texture2D texture;
    raylib::Color color;
    float         radius;
    // Additional rendering data like size, rotation, etc. can be added here
};

struct RaySensorComponent
{
    float offset{0.F};
    float range{100.F};

    std::vector<float>           ray_angles;
    std::vector<raylib::Vector2> hits;
    std::vector<Pixel>           pixels_until_hit;
};
