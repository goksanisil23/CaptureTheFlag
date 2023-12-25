#include "RenderSystem.h"

#include "Bresenham.hpp"

RenderSystem::RenderSystem(const std::string &map_path)
{
    SetTraceLogLevel(LOG_ERROR);

    window_ = std::make_unique<raylib::Window>(kScreenWidth, kScreenHeight, "");
    window_->SetPosition(40, 20);

    raylib::Image map_image{raylib::LoadImage(map_path)};
    map_texture_ = LoadTextureFromImage(map_image);
    map_image.Unload();

    // We draw in this texture manner since we want to get pixel values
    render_target_ = LoadRenderTexture(kScreenWidth, kScreenHeight);

    // Create a render texture to draw on
    BeginTextureMode(render_target_);
    DrawTexture(map_texture_, 0, 0, WHITE);
    EndTextureMode();
}

void RenderSystem::activateDrawing()
{
    render_target_.BeginMode();
    DrawTexture(map_texture_, 0, 0, WHITE);
}

void RenderSystem::disableDrawing()
{
    render_target_.EndMode();
}

void RenderSystem::loadRenderBufferCPU()
{
    render_buffer_.Load(render_target_.texture);
}

void RenderSystem::render()
{
    // Update the render texture with the potentially manipulated CPU texture buffer
    UpdateTexture(render_target_.texture, render_buffer_.data);

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

void RenderSystem::drawAgentsDirect(const std::vector<Agent> &agents)
{
    for (auto const &agent : agents)
    {
        agent.tf.position.DrawCircle(10, agent.vis.color);
        // Draw heading line for robot
        raylib::Vector2 heading_end   = {agent.tf.position.x + agent.vis.radius * cos(DEG2RAD * agent.tf.rotation),
                                         agent.tf.position.y + agent.vis.radius * -sin(DEG2RAD * agent.tf.rotation)};
        auto            heading_color = raylib::Color::White();
        heading_color.DrawLine(agent.tf.position, heading_end);
    }
}

void RenderSystem::drawAgents(const std::vector<Agent> &agents)
{
    for (auto const &agent : agents)
    {
        // raylib::Color   color = (agent.crashed_) ? raylib::Color((Color){253, 249, 0, 150}) : agent.color_;
        raylib::Vector2 agent_texture_coord{agent.tf.position.x, kScreenHeight - agent.tf.position.y};
        render_buffer_.DrawCircle(agent_texture_coord, agent.vis.radius, agent.vis.color);
    }
}

void RenderSystem::stepSensors(std::vector<Agent> &agents)
{
    for (auto &agent : agents)
    {
        float ray_start_x, ray_start_y;
        float agent_rot_rad = agent.tf.rotation * DEG2RAD; // Convert angle to radians

        ray_start_x = agent.tf.position.x + agent.sensor.offset * cos(DEG2RAD * agent.tf.rotation);
        ray_start_y = kScreenHeight - agent.tf.position.y + agent.sensor.offset * -sin(DEG2RAD * agent.tf.rotation);

        if (agent.has_sensor)
        {
            agent.sensor.hits.clear();
            agent.sensor.pixels_until_hit.clear();
            for (const auto angle : agent.sensor.ray_angles)
            {
                const float end_pos_x = ray_start_x + agent.sensor.range * cos(DEG2RAD * (agent.tf.rotation + angle));
                const float end_pos_y = ray_start_y + agent.sensor.range * -sin(DEG2RAD * (agent.tf.rotation + angle));

                auto pixels_along_ray = bresenham<Pixel>(ray_start_x, ray_start_y, end_pos_x, end_pos_y);
                bool hit_found{false};
                for (const auto pix : pixels_along_ray)
                {
                    // We check for the sensor hit based on the boundaries which are determined by the color
                    const int   pix_idx{pix.y * render_buffer_.width + pix.x};
                    const Color pix_color = reinterpret_cast<Color *>(render_buffer_.data)[pix_idx];
                    if (!isDrivablePixel(pix_color))
                    {
                        // Calculate hit point relative to the robot
                        raylib::Vector2 hit_pt_relative;
                        float           xTranslated = pix.x - ray_start_x;
                        float           yTranslated = pix.y - ray_start_y;
                        hit_pt_relative.x = xTranslated * cos(agent_rot_rad) - yTranslated * sin(agent_rot_rad);
                        hit_pt_relative.y = xTranslated * sin(agent_rot_rad) + yTranslated * cos(agent_rot_rad);
                        agent.sensor.hits.push_back(hit_pt_relative);
                        hit_found = true;
                        break;
                    }
                    else if (Agent::kDrawSensorRays) // drawing ray paths
                    {
                        // std::cout << pix.x << " " << pix.y << std::endl;
                        agent.sensor.pixels_until_hit.push_back(pix);
                    }
                }
                if (!hit_found) // If no hit is found, instead of no return, we report the max range
                {
                    raylib::Vector2 max_range_pt_relative;
                    float           xTranslated = end_pos_x - ray_start_x;
                    float           yTranslated = end_pos_y - ray_start_y;
                    max_range_pt_relative.x     = xTranslated * cos(agent_rot_rad) - yTranslated * sin(agent_rot_rad);
                    max_range_pt_relative.y     = xTranslated * sin(agent_rot_rad) + yTranslated * cos(agent_rot_rad);
                    agent.sensor.hits.push_back(max_range_pt_relative);
                }
            }
        }
    }
}

void RenderSystem::drawSensors(std::vector<Agent> &agents)
{
    for (auto &agent : agents)
    {
        for (const auto &pix : agent.sensor.pixels_until_hit)
        {
            render_buffer_.DrawPixel(pix.x, pix.y, raylib::Color::DarkPurple());
        }
        agent.sensor.pixels_until_hit.clear();
    }
}

bool RenderSystem::isDrivablePixel(const raylib::Color &pixel_color) const
{
    if ((pixel_color == kDrivableAreaColor))
    {
        return true;
    }
    return false;
}

bool RenderSystem::isBarrierPixel(const raylib::Color &pixel_color) const
{
    if ((pixel_color == kBarrierColor))
    {
        return true;
    }
    return false;
}

// bool RenderSystem::isEnemyPixel(const raylib::Color &pixel_color, const raylib::Color &own_color)
// {
//     if ((pixel_color == kBarrierColor))
//     {
//         return true;
//     }
//     return false;
// }