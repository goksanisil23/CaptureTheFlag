#pragma once

#include <vector>

template <typename TContainer2D>
std::vector<TContainer2D> bresenham(const int &x0, const int &y0, const int &x1, const int &y1)
{
    std::vector<TContainer2D> pixels;

    const auto dx = std::abs(x1 - x0);
    const auto dy = std::abs(y1 - y0);

    auto x = x0;
    auto y = y0;

    int sx = (x0 > x1) ? -1 : 1;
    int sy = (y0 > y1) ? -1 : 1;

    if (dx > dy)
    {
        auto err = dx / 2.0F;
        while (x != x1)
        {
            pixels.push_back({x, y});
            err -= dy;
            if (err < 0.)
            {
                y += sy;
                err += dx;
            }
            x += sx;
        }
    }
    else
    {
        auto err = dy / 2.0;
        while (y != y1)
        {
            pixels.push_back({x, y});
            err -= dx;
            if (err < 0)
            {
                x += sx;
                err += dy;
            }
            y += sy;
        }
    }

    pixels.push_back({x, y});

    return pixels;
}