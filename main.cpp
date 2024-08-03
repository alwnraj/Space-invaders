#include "raylib.h"
#include "game.h"
#include "alien.h"
#include <string>


int main(void)
{
    Color grey = { 29, 29, 27, 255 };
    Color yellow = { 243, 216, 63, 255 };


    InitWindow(800, 800, "Space Invaders");
    SetTargetFPS(60);
    Font font = LoadFontEx("monogram.ttf", 64, 0, 0);
    Texture2D spaceship = LoadTexture("spaceship.png");

    Game game;
    

    while (!WindowShouldClose())
    {
        game.HandleInput();
        game.Update();
        BeginDrawing();
        ClearBackground(grey);
        DrawRectangleRoundedLines({ 10,10,780,780 }, 0.18f, 20, 2, ORANGE);
        DrawLineEx({ 20, 730 }, { 780, 730 }, 3, ORANGE); // Draws the line below which is the score and the lives indicator

        if (game.run) {
            DrawTextEx(font, "LEVEL 1", { 570,740 }, 34, 2, ORANGE);
        }
        else
        {
            DrawTextEx(font, "GAME OVER!", { 570,740 }, 34, 2, RED);
        }

        float x = 50.0;
        for (int i = 0; i < game.Lives; i++) {
            DrawTextureV(spaceship, { x, 745 }, ORANGE);
            x += 50;
        }

        DrawTextEx(font, "SCORE", { 50,15 }, 34, 2, ORANGE);

        std::string numbertext = std::to_string(game.score); //Counts the score
       /* int leadingzeros = 5 - numbertext.length();
        numbertext = std::string(leadingzeros, '0') + numbertext;*/
        DrawTextEx(font, numbertext.c_str(), { 50,40 }, 34, 2, ORANGE);

        game.Draw();
        EndDrawing();
    }

    CloseWindow();

    return 0;
}