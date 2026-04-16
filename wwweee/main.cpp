#include <raylib.h>
#include <vector>
#include <string>
#include <iostream>
#include "game.h"


/**
 * @brief Formatuje liczbę całkowitą, dodając zera wiodące.
 *
 * Funkcja przyjmuje liczbę i pożądaną szerokość ciągu znaków. Jeśli liczba
 * jest krótsza niż `width`, zostaną dodane zera z przodu.
 *
 * @param number Liczba do sformatowania.
 * @param width Całkowita szerokość wynikowego ciągu znaków.
 * @return Sformatowany ciąg znaków z zerami wiodącymi.
 */
std::string FormatWithLeadingZeros(int number, int width) {
    std::string numberText = std::to_string(number);
    int leadingZeros = width - numberText.length();
    return numberText = std::string(leadingZeros, '0') + numberText;
}

/**
 * @brief Główna funkcja programu.
 *
 * Inicjalizuje okno gry, zasoby audio, ładuje czcionki i tekstury,
 * a następnie zarządza główną pętlą gry, w tym menu początkowym,
 * wyświetlaniem najlepszego wyniku, aktualizacjami gry i rysowaniem.
 * Obsługuje również stany gry (menu, rozgrywka, koniec gry) i nawigację między nimi.
 *
 * @return Kod zakończenia programu.
 */
int main()
{
    Color grey = { 29, 29, 27, 255 };
    Color blue = { 173, 216, 230, 255 };
    int offset = 50;
    int windowWidth = 750;
    int windowHeight = 700;

    InitWindow(windowWidth + offset, windowHeight + 2 * offset, "KAPITAN BOMBA");
    InitAudioDevice();

    Font font = LoadFontEx("Font/monogram.ttf", 64, 0, 0);
    Texture2D spaceshipImage = LoadTexture("Graphics/spaceship.png");

    SetTargetFPS(60);

    Game game;
    bool showMenu = true;
    while (WindowShouldClose() == false) {
        UpdateMusicStream(game.music);

        // MENU GŁÓWNE
        if (showMenu) {
            if (IsKeyPressed(KEY_ENTER)) {
                game.Reset();
                showMenu = false;
                game.run = true;
            }

            BeginDrawing();
            ClearBackground(grey);

            DrawTextEx(font, "KAPITAN BOMBA", { 100, 200 }, 50, 4, blue);
            DrawTextEx(font, "PRESS ENTER TO START", { 100, 300 }, 32, 2, blue);
            DrawTextEx(font, "PRESS H TO SEE THE HIGHEST SCORE", { 100, 400 }, 32, 2, blue);
            DrawTextEx(font, "INSTRUCTIONS:", { 100, 500 }, 24, 2, blue);
            DrawTextEx(font, "USE WASD TO MOVE", { 100, 560 }, 24, 2, blue);
            DrawTextEx(font, "PRESS LMB TO SHOOT", { 100, 620 }, 24, 2, blue);
            if (IsKeyPressed(KEY_H)) {
                while (!IsKeyPressed(KEY_B)) {
                    UpdateMusicStream(game.music);
                    BeginDrawing();
                    ClearBackground(grey);

                    std::string highscoreText = FormatWithLeadingZeros(game.highscore, 5);
                    DrawTextEx(font, "HIGH-SCORE", { 160, 200 }, 40, 2, blue);
                    DrawTextEx(font, highscoreText.c_str(), { 160, 250 }, 40, 2, blue);
                    DrawTextEx(font, "PRESS B TO GO BACK TO MENU", { 160, 600 }, 28, 2, blue);

                    EndDrawing();
                }

            }
            EndDrawing();
            continue;
        }
        game.HandleInput();
        game.Update();
        BeginDrawing();
        ClearBackground(grey);
        game.Draw();
        DrawLineEx({ -10, 750 }, { 810, 750 }, 100, DARKBLUE);

        if (game.run && game.score < 2000) {
            DrawTextEx(font, "LEVEL 01", { 570, 740 }, 34, 4, blue);
        }if
            (game.run && game.score > 2000 && game.score < 4000) {

            DrawTextEx(font, "LEVEL 02", { 570, 740 }, 34, 4, blue);
            game.alienSpawnInterval = 2.5f;

        }if
            (game.run && game.score > 4000) {

            DrawTextEx(font, "LEVEL 03", { 570, 740 }, 34, 4, blue);
            game.alienSpawnInterval = 2.0f;

        }
        else if
            (game.run == false) {
            DrawTextEx(font, "GAME OVER", { 570, 740 }, 34, 4, blue);
        }
        float x = 50.0;
        for (int i = 0; i < game.lives; i++) {
            DrawTextureV(spaceshipImage, { x, 745 }, WHITE);
            x += 50;
        }

        DrawTextEx(font, "SCORE", { 50, 15 }, 34, 2, blue);
        std::string scoreText = FormatWithLeadingZeros(game.score, 5);
        DrawTextEx(font, scoreText.c_str(), { 50, 40 }, 34, 2, blue);

        DrawTextEx(font, "HIGH-SCORE", { 570, 15 }, 34, 2, blue);
        std::string highscoreText = FormatWithLeadingZeros(game.highscore, 5);
        DrawTextEx(font, highscoreText.c_str(), { 655, 40 }, 34, 2, blue);


        if (!game.run && !showMenu) {
            DrawTextEx(font, "PRESS R TO GO BACK TO MENU", { 160, 200 }, 32, 4, blue);
            DrawTextEx(font, "OR ENTER TO START NEW GAME", { 160, 240 }, 32, 4, blue);
            if (IsKeyPressed(KEY_R)) {
                game.Reset();
                showMenu = true;
            }
        }

        EndDrawing();
    }


    CloseWindow();
    CloseAudioDevice();
    return 0; // Dodano brakujący return 0; dla funkcji main
}