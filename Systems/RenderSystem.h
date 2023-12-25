#pragma once

#include <iostream>
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
    // loads the current texture buffer from GPU to CPU
    // NOTE: Y-coordinate will be inverted in the CPU buffer.
    void loadRenderBufferCPU();

    // Draw the agents manually on the CPU texture buffer (inverted Y-axis)
    void drawAgents(const std::vector<Agent> &agents);
    // Draw the agents directly on the GPU buffer
    void drawAgentsDirect(const std::vector<Agent> &agents);

    // Applies the raycast logic on the CPU texture buffer, per agent
    // If enabled, draws the rays as well.
    void stepSensors(std::vector<Agent> &agents);
    void drawSensors(std::vector<Agent> &agents);

    bool isBarrierPixel(const raylib::Color &pixel_color) const;
    bool isDrivablePixel(const raylib::Color &pixel_color) const;

  private:
    std::unique_ptr<raylib::Camera2D> camera_;
    std::unique_ptr<raylib::Window>   window_;
    raylib::RenderTexture             render_target_;

    // Used to store the texture buffer on CPU on each tick
    raylib::Image render_buffer_;

    raylib::Texture2D map_texture_;
};