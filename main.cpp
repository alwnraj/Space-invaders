#include "raylib.h"
#include "game.h"
#include "alien.h"

int main(void)
{
    Color grey = { 29, 29, 27, 255 };
    Color yellow = { 243, 216, 63, 255 };

    int offset = 50;


    InitWindow(750 + offset, 700 + offset, "Space Invaders");
    SetTargetFPS(60);

    Game game;
    

    while (!WindowShouldClose())
    {
        game.HandleInput();
        game.Update();
        BeginDrawing();
        ClearBackground(grey);
        DrawRectangleRoundedLines({ 10,10,780,780 }, 0.18f, 20, 2, yellow);
        game.Draw();
        EndDrawing();
    }

    CloseWindow();

    return 0;
}