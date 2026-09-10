#include "raylib.h"
#include "Constants.h"
#include "Agent.h"
#include <vector>

using namespace std;

int main(int, char**){
    InitWindow(GameConfig::SCREEN_WIDTH, GameConfig::SCREEN_HEIGHT, "Behavior Agents");
    SetTargetFPS(GameConfig::TARGET_FPS);

    vector<Agent> agents;
    for(int i = 0; i< 50; i++) {
        float x = static_cast<float>(GetRandomValue(0, GameConfig::SCREEN_WIDTH));
        float y = static_cast<float>(GetRandomValue(0, GameConfig::SCREEN_HEIGHT));
        agents.push_back(Agent(Vector2({x, y})));
    }

    while(!WindowShouldClose()){
        Vector2 targetMouse = GetMousePosition();
        float deltaTime = GetFrameTime();

        for( Agent& agent : agents) {
            agent.update(agents, deltaTime);
        }


        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawCircleV(targetMouse, 10.0f, RED); //Mouse Representation

        for( const Agent& agent : agents) {
            agent.draw();
        }
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
