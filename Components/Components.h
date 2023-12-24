#pragma once

#include "raylib-cpp.hpp"

struct PositionComponent
{
    raylib::Vector2 position;
};

struct RenderComponent
{
    // raylib::Texture2D texture;
    raylib::Color color;
    // Additional rendering data like size, rotation, etc. can be added here
};
