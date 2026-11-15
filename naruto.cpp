#include <raylib.h>
#include <iostream>
using namespace std;

int main()
{
    int counter = 0;

    InitWindow(1080, 700, "ShooterCpp");
    InitAudioDevice();
    SetTargetFPS(60);

    // Background music
    Music bgm1 = LoadMusicStream("../assets/akatsuki_theme.mp3");
    SetMusicVolume(bgm1, 0.7f);
    PlayMusicStream(bgm1);

    // Load characters
    Texture2D narutoTex = LoadTexture("../assets/naruto.png");
    Texture2D sasukeTex = LoadTexture("../assets/madara.png");

    // Player 1: Naruto
    int p1x = 50;
    int p1y = 350;

    // Player 2: Sasuke
    int p2x = 850;
    int p2y = 350;

    // Character sizes
    float playerScale = 0.30f;

    // Jump variables
    bool jumpP1 = false;
    bool fallingP1 = false;

    bool jumpP2 = false;
    bool fallingP2 = false;

    // Animated background
    int animFrames = 0;
    Image animImage = LoadImageAnim("../assets/bg.gif", &animFrames);

    Texture2D animTexture = {0, 0, 0, 0, 0};

    if (animFrames > 0)
    {
        Image firstFrame = {
            .data = animImage.data,
            .width = animImage.width,
            .height = animImage.height,
            .mipmaps = 1,
            .format = animImage.format
        };

        animTexture = LoadTextureFromImage(firstFrame);
    }

    int currentAnimFrame = 0;
    int frameCounter = 0;
    int frameDelay = 8;

    // Game variables
    bool gameStart = false;
    int colorFlag = 0;

    Rectangle bgSource = {0, 0, 0, 0};
    Rectangle bgDest = {0, 0, 1080, 700};

    if (animFrames > 0)
    {
        bgSource = {
            0,
            0,
            (float)animImage.width,
            (float)animImage.height
        };
    }

    while (!WindowShouldClose())
    {
        UpdateMusicStream(bgm1);

        // Background animation
        frameCounter++;

        if (animFrames > 0 && frameCounter >= frameDelay)
        {
            currentAnimFrame++;

            if (currentAnimFrame >= animFrames)
                currentAnimFrame = 0;

            int frameSize = GetPixelDataSize(
                animImage.width,
                animImage.height,
                animImage.format
            );

            unsigned int nextFrameDataOffset =
                frameSize * currentAnimFrame;

            UpdateTexture(
                animTexture,
                (unsigned char*)animImage.data + nextFrameDataOffset
            );

            frameCounter = 0;
        }

        BeginDrawing();

        // INTRO SCREEN
        if (!gameStart)
        {
            if (counter <= 300)
            {
                ClearBackground(BLACK);

                DrawText(
                    "A GAME BY",
                    460, 300, 30, WHITE
                );

                counter++;
                EndDrawing();
                continue;
            }

            if (counter <= 600)
            {
                ClearBackground(BLACK);

                DrawText(
                    "Muzamil Hussain",
                    340, 300, 60, YELLOW
                );

                counter++;
                EndDrawing();
                continue;
            }

            // Animated background
            ClearBackground(BLACK);

            if (animFrames > 0)
            {
                DrawTexturePro(
                    animTexture,
                    bgSource,
                    bgDest,
                    {0, 0},
                    0,
                    WHITE
                );
            }

            DrawText(
                "PRESS P TO START",
                400, 580, 30,
                colorFlag % 10 == 0 ? YELLOW : WHITE
            );

            if (IsKeyPressed(KEY_P))
            {
                gameStart = true;
                counter = 0;
            }
        }

        // GAME SCREEN
        else
        {
            // Fight intro
            if (counter <= 200)
            {
                counter++;

                ClearBackground(BLACK);

                if (animFrames > 0)
                {
                    DrawTexturePro(
                        animTexture,
                        bgSource,
                        bgDest,
                        {0, 0},
                        0,
                        WHITE
                    );
                }

                DrawText(
                    "FIGHT!",
                    450, 300, 50, WHITE
                );

                EndDrawing();
                continue;
            }

            // Draw animated background
            ClearBackground(BLACK);

            if (animFrames > 0)
            {
                DrawTexturePro(
                    animTexture,
                    bgSource,
                    bgDest,
                    {0, 0},
                    0,
                    WHITE
                );
            }

            // NARUTO CONTROLS
            if (IsKeyDown(KEY_D))
                p1x += 5;

            if (IsKeyDown(KEY_A))
                p1x -= 5;

            if (IsKeyPressed(KEY_SPACE) && !jumpP1 && !fallingP1)
                jumpP1 = true;

            // Naruto jumping
            if (jumpP1)
            {
                p1y -= 15;

                if (p1y <= 200)
                {
                    jumpP1 = false;
                    fallingP1 = true;
                }
            }

            if (fallingP1)
            {
                p1y += 15;

                if (p1y >= 350)
                {
                    p1y = 350;
                    fallingP1 = false;
                }
            }

            // SASUKE CONTROLS
            if (IsKeyDown(KEY_RIGHT))
                p2x += 5;

            if (IsKeyDown(KEY_LEFT))
                p2x -= 5;

            if (IsKeyPressed(KEY_UP) && !jumpP2 && !fallingP2)
                jumpP2 = true;

            // Sasuke jumping
            if (jumpP2)
            {
                p2y -= 15;

                if (p2y <= 200)
                {
                    jumpP2 = false;
                    fallingP2 = true;
                }
            }

            if (fallingP2)
            {
                p2y += 15;

                if (p2y >= 350)
                {
                    p2y = 350;
                    fallingP2 = false;
                }
            }

            // Keep characters inside screen
            if (p1x < 0) p1x = 0;
            if (p1x > 1080 - narutoTex.width * playerScale)
                p1x = 1080 - narutoTex.width * playerScale;

            if (p2x < 0) p2x = 0;
            if (p2x > 1080 - sasukeTex.width * playerScale)
                p2x = 1080 - sasukeTex.width * playerScale;

            // Draw Naruto (smaller)
            Rectangle narutoSource = {
                0, 0,
                (float)narutoTex.width,
                (float)narutoTex.height
            };

            Rectangle narutoDest = {
                (float)p1x,
                (float)p1y,
                narutoTex.width * playerScale,
                narutoTex.height * playerScale
            };

            DrawTexturePro(
                narutoTex,
                narutoSource,
                narutoDest,
                {0, 0},
                0,
                WHITE
            );

            // Draw Sasuke (second character)
            Rectangle sasukeSource = {
                0, 0,
                (float)sasukeTex.width,
                (float)sasukeTex.height
            };

            Rectangle sasukeDest = {
                (float)p2x,
                (float)p2y,
                sasukeTex.width * playerScale,
                sasukeTex.height * playerScale
            };

            DrawTexturePro(
                sasukeTex,
                sasukeSource,
                sasukeDest,
                {0, 0},
                0,
                WHITE
            );
        }

        EndDrawing();

        if (colorFlag >= 100)
            colorFlag = 0;

        colorFlag++;
    }

    // Cleanup
    UnloadTexture(narutoTex);
    UnloadTexture(sasukeTex);
    UnloadTexture(animTexture);
    UnloadImage(animImage);

    UnloadMusicStream(bgm1);

    CloseAudioDevice();
    CloseWindow();

    return 0;
}