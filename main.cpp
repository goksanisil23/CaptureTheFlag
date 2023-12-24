#include <iomanip>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

#include "Entities/Agent.h"
#include "Systems/RenderSystem.h"

int main(int argc, char **argv)
{
    auto render_sys = RenderSystem("../MapCreator/build/map_image.png");

    std::vector<Agent> agents;
    agents.push_back(Agent());

    while (true)
    {
        // -------- 1) Kinematics Update of Agents -------- //
        for (auto &agent : agents)
        {
            agent.move();
        }

        // -------- 2) Draw current state of actors and static entities -------- //
        render_sys.activateDrawing();
        // Draw track title and other static entities
        // DrawCircle(100, 100, 20, {255, 255, 255, 255});

        render_sys.disableDrawing();

        // -------- 3) Direct render buffer manipulation for sensors -------- //
        // NOTE: Y-coordinate will be inverted
        raylib::Image render_buffer;
        render_buffer.Load(render_sys.render_target_.texture);

        render_sys.drawAgents(agents, render_buffer);

        // // Do some changes to render buffer
        UpdateTexture(render_sys.render_target_.texture, render_buffer.data);

        // Finalize the render
        render_sys.render();
    }
    return 0;
}
