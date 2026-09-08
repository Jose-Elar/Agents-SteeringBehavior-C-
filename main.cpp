#include "raylib.h"
#include "Constants.h"
#include "Agent.h"

int main(int, char**){
    InitWindow(GameConfig::SCREEN_WIDTH, GameConfig::SCREEN_HEIGHT, "Behavior Agents");
    SetTargetFPS(GameConfig::TARGET_FPS);

    Agent agent(Vector2(500.0f,300.0f));

    while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(RAYWHITE);
        agent.draw();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
