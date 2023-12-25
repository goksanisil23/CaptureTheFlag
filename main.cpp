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
    agents.push_back(Agent({100, 100}, raylib::Color::Green(), 10.F));
    agents.push_back(Agent({1000, 700}, raylib::Color::Green(), 10.F));

    while (true)
    {
        // -------- 1) Kinematics Update of Agents -------- //
        // TODO: Decision making using the last updated sensor measurements here
        for (auto &agent : agents)
        {
            agent.move();
        }

        // -------- 2) Draw current state of actors and static entities -------- //
        render_sys.activateDrawing();

        // We want agents to see each other so we first draw them before sensor update
        render_sys.drawAgentsDirect(agents);

        render_sys.disableDrawing();

        // -------- 3) Direct render buffer manipulation for sensors -------- //
        // Either inspect or do some changes to render buffer
        render_sys.loadRenderBufferCPU();
        // render_sys.drawAgents(agents);

        render_sys.stepSensors(agents);
        render_sys.drawSensors(agents);

        // Finalize the render
        render_sys.render();
    }
    return 0;
}
