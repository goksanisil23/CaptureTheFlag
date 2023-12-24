#include "raylib.h"

int main()
{
    // Initialization
    const int screenWidth  = 1600;
    const int screenHeight = 1400;

    InitWindow(screenWidth, screenHeight, "raylib - Draw on Background");

    // Load the saved map image as a texture
    Image     mapImage   = LoadImage("../MapCreator/build/map_image.png");
    Texture2D mapTexture = LoadTextureFromImage(mapImage);
    UnloadImage(mapImage);

    // Create a render texture to draw on
    RenderTexture2D target = LoadRenderTexture(screenWidth, screenHeight);
    BeginTextureMode(target);
    DrawTexture(mapTexture, 0, 0, WHITE); // Draw the background image
    EndTextureMode();

    SetTargetFPS(60);
    float x = 10;

    // Main game loop
    while (!WindowShouldClose())
    {
        // Update (add your game logic here)

        // Additional drawing on target
        BeginTextureMode(target);
        DrawTexture(mapTexture, 0, 0, WHITE);
        // Draw anything you want over the background here
        // For example, DrawCircle(...), DrawRectangle(...), etc.
        DrawCircle(x, 100, 20, WHITE);
        EndTextureMode();

        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw the render texture
        DrawTextureRec(
            target.texture, (Rectangle){0, 0, target.texture.width, -target.texture.height}, (Vector2){0, 0}, WHITE);

        EndDrawing();
        x += 0.1;
    }

    // De-Initialization
    UnloadTexture(mapTexture);   // Unload map texture
    UnloadRenderTexture(target); // Unload render texture
    CloseWindow();

    return 0;
}
