#pragma once

#include <math.h>
#include <vector>

#include "raylib-cpp.hpp"

struct Pixel
{
    int x{};
    int y{};
};

constexpr int kScreenWidth  = 1600;
constexpr int kScreenHeight = 1400;

const raylib::Color kTeam1Color{raylib::Color::Blue()};
const raylib::Color kTeam2Color{raylib::Color::Green()};

const raylib::Color kBarrierColor{raylib::Color::Red()};
const raylib::Color kDrivableAreaColor{raylib::Color::Black()};