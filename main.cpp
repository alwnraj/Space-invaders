#include "raylib.h"
#include "game.h"

int main(void)
{
    Color grey = { 29, 29, 27, 255 };


    InitWindow(750, 700, "Space Invaders");
    SetTargetFPS(60);

    Game game;

    while (!WindowShouldClose())
    {
        game.HandleInput();

        BeginDrawing();
        ClearBackground(grey);

        game.Draw();

        EndDrawing();
    }

    CloseWindow();

    return 0;
}