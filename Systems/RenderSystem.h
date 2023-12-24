#pragma once

#include <memory>

#include "Typedefs.h"
#include "raylib-cpp.hpp"

#include "../Entities/Agent.h"

class RenderSystem
{
  public:
    RenderSystem() = delete;
    RenderSystem(const std::string &map_path);

    void activateDrawing();
    void disableDrawing();
    void render();

    void drawAgents(const std::vector<Agent> &agents, raylib::Image &render_buffer);

    std::unique_ptr<raylib::Camera2D> camera_;
    std::unique_ptr<raylib::Window>   window_;
    raylib::RenderTexture             render_target_;
    raylib::Image                     current_frame_;

    raylib::Texture2D map_texture_;
};