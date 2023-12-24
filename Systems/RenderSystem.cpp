#include "RenderSystem.h"

RenderSystem::RenderSystem(const std::string &map_path)
{
    SetTraceLogLevel(LOG_ERROR);

    window_ = std::make_unique<raylib::Window>(kScreenWidth, kScreenHeight, "");
    window_->SetPosition(40, 20);

    raylib::Image map_image{raylib::LoadImage(map_path)};
    map_texture_ = LoadTextureFromImage(map_image);
    map_image.Unload();

    // // We draw in this texture manner since we want to get pixel values
    render_target_ = LoadRenderTexture(kScreenWidth, kScreenHeight);

    // Create a render texture to draw on
    // RenderTexture2D target = LoadRenderTexture(kScreenWidth, kScreenHeight);
    BeginTextureMode(render_target_);
    DrawTexture(map_texture_, 0, 0, WHITE); // Draw the background image
    EndTextureMode();
}

void RenderSystem::activateDrawing()
{
    render_target_.BeginMode();
    DrawTexture(map_texture_, 0, 0, WHITE); // Draw the background image
}

void RenderSystem::disableDrawing()
{
    render_target_.EndMode();
}

void RenderSystem::render()
{
    window_->BeginDrawing();
    ClearBackground(BLACK);
    render_target_.GetTexture().Draw({0.F,
                                      0.F,
                                      static_cast<float>(render_target_.texture.width),
                                      static_cast<float>(-render_target_.texture.height)},
                                     {0.F, 0.F},
                                     WHITE);
    window_->DrawFPS();
    window_->EndDrawing();
}

void RenderSystem::drawAgents(const std::vector<Agent> &agents, raylib::Image &render_buffer)
{
    for (auto const &agent : agents)
    {
        // raylib::Color   color = (agent.crashed_) ? raylib::Color((Color){253, 249, 0, 150}) : agent.color_;
        raylib::Vector2 agent_texture_coord{agent.pos.position.x, kScreenHeight - agent.pos.position.y};
        render_buffer.DrawCircle(agent_texture_coord, 10, agent.vis.color);
    }
}