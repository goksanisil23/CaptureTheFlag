#include "raylib.h"

#include "Typedefs.h"

int main()
{
    InitWindow(kScreenWidth, kScreenHeight, "raylib - Simple Map Editor");

    RenderTexture2D target = LoadRenderTexture(kScreenWidth, kScreenHeight);
    BeginTextureMode(target);
    ClearBackground(BLACK);
    EndTextureMode();

    Vector2   mousePosition;
    bool      isDrawing         = false;
    const int squareSize        = 10;
    int       boundaryThickness = 10;

    SetTargetFPS(60);

    // Main game loop
    while (!WindowShouldClose())
    {
        // Update
        mousePosition = GetMousePosition();

        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
        {
            isDrawing = true;
            BeginTextureMode(target);
            DrawRectangleV((Vector2){mousePosition.x - squareSize / 2, mousePosition.y - squareSize / 2},
                           (Vector2){squareSize, squareSize},
                           RED); // Draw square
                                 // Boundary
            DrawRectangle(0, 0, kScreenWidth, boundaryThickness, RED);
            // Bottom border
            DrawRectangle(0, kScreenHeight - boundaryThickness, kScreenWidth, boundaryThickness, RED);
            // Left border
            DrawRectangle(0, 0, boundaryThickness, kScreenHeight, RED);
            // Right border
            DrawRectangle(kScreenWidth - boundaryThickness, 0, boundaryThickness, kScreenHeight, RED);

            EndTextureMode();
        }
        else
        {
            isDrawing = false;
        }

        // Draw
        BeginDrawing();
        ClearBackground(BLACK);

        DrawTextureRec(
            target.texture, (Rectangle){0, 0, target.texture.width, -target.texture.height}, (Vector2){0, 0}, WHITE);

        if (isDrawing)
        {
            DrawRectangleV((Vector2){mousePosition.x - squareSize / 2, mousePosition.y - squareSize / 2},
                           (Vector2){squareSize, squareSize},
                           RED); // Preview of square
        }

        EndDrawing();

        // Save to image on exit
        if (WindowShouldClose())
        {
            Image image = LoadImageFromTexture(target.texture);
            ExportImage(image, "map_image.png");
            UnloadImage(image);
        }
    }

    // De-Initialization
    UnloadRenderTexture(target);
    CloseWindow();

    return 0;
}
