#include "raylib.h"
#include "raymath.h"

#define MAX_ITEMS 8

typedef struct
{
    Vector3 position;
    float radius;
    bool active;
    Color color;
} Collectible;

int main(void)
{
    // 1. INITIALIZATION
    const int screenWidth = 1024;
    const int screenHeight = 768;
    InitWindow(screenWidth, screenHeight, "Raylib 3D - Island Collector");

    // Setup 3D First-Person Camera
    Camera3D camera = {0};
    camera.position = (Vector3){0.0f, 2.0f, 10.0f};
    camera.target = (Vector3){0.0f, 2.0f, 0.0f};
    camera.up = (Vector3){0.0f, 1.0f, 0.0f};
    camera.fovy = 60.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    // Lock cursor to center of screen for FPS mouse look
    DisableCursor();

    // Player State
    float playerRadius = 0.6f;
    int score = 0;

    // Generate Collectible Orbs
    Collectible items[MAX_ITEMS] = {
        {(Vector3){5.0f, 1.0f, 5.0f}, 0.5f, true, GOLD},
        {(Vector3){-7.0f, 1.0f, 3.0f}, 0.5f, true, GOLD},
        {(Vector3){3.0f, 1.0f, -8.0f}, 0.5f, true, GOLD},
        {(Vector3){-6.0f, 1.0f, -6.0f}, 0.5f, true, GOLD},
        {(Vector3){10.0f, 1.0f, -2.0f}, 0.5f, true, GOLD},
        {(Vector3){-4.0f, 1.0f, 10.0f}, 0.5f, true, GOLD},
        {(Vector3){8.0f, 1.0f, 8.0f}, 0.5f, true, GOLD},
        {(Vector3){0.0f, 1.0f, -12.0f}, 0.5f, true, GOLD}};

    // Obstacles (Trees/Pillars) for 3D Bounding-Box Collisions
    BoundingBox obstacles[3] = {
        {(Vector3){-2.0f, 0.0f, -2.0f}, (Vector3){-1.0f, 4.0f, -1.0f}},
        {(Vector3){4.0f, 0.0f, -3.0f}, (Vector3){5.5f, 5.0f, -1.5f}},
        {(Vector3){-5.0f, 0.0f, 4.0f}, (Vector3){-3.5f, 3.5f, 5.5f}}};

    SetTargetFPS(60);

    // 2. MAIN GAME LOOP
    while (!WindowShouldClose())
    {
        // Save current position prior to camera update (for collision rollback)
        Vector3 oldPosition = camera.position;

        // Update First-Person Mouse + WASD Controls
        UpdateCamera(&camera, CAMERA_FIRST_PERSON);

        // Keep player on ground plane (Y = 2.0 height)
        camera.position.y = 2.0f;

        // AABB Collision Detection against obstacles
        BoundingBox playerBox = {
            (Vector3){camera.position.x - playerRadius, 0.0f, camera.position.z - playerRadius},
            (Vector3){camera.position.x + playerRadius, 2.5f, camera.position.z + playerRadius}};

        for (int i = 0; i < 3; i++)
        {
            if (CheckCollisionBoxes(playerBox, obstacles[i]))
            {
                // Restore previous position on collision
                camera.position = oldPosition;
                break;
            }
        }

        // Sphere Collision Detection against collectibles
        for (int i = 0; i < MAX_ITEMS; i++)
        {
            if (items[i].active)
            {
                if (CheckCollisionSpheres(camera.position, playerRadius, items[i].position, items[i].radius))
                {
                    items[i].active = false;
                    score += 100;
                }
            }
        }

        // 3. DRAWING
        BeginDrawing();
        ClearBackground(SKYBLUE);

        BeginMode3D(camera);
        // Draw Ground / Sea Base
        DrawPlane((Vector3){0.0f, 0.0f, 0.0f}, (Vector2){60.0f, 60.0f}, DARKGREEN);

        // Draw Obstacles
        for (int i = 0; i < 3; i++)
        {
            Vector3 size = Vector3Subtract(obstacles[i].max, obstacles[i].min);
            Vector3 center = Vector3Add(obstacles[i].min, Vector3Scale(size, 0.5f));
            DrawCube(center, size.x, size.y, size.z, BROWN);
            DrawCubeWires(center, size.x, size.y, size.z, DARKBROWN);
        }

        // Draw Collectible Orbs
        for (int i = 0; i < MAX_ITEMS; i++)
        {
            if (items[i].active)
            {
                DrawSphere(items[i].position, items[i].radius, items[i].color);
                DrawSphereWires(items[i].position, items[i].radius + 0.05f, 8, 8, ORANGE);
            }
        }

        // Draw World Grid
        DrawGrid(30, 2.0f);
        EndMode3D();

        // 2D HUD Overlay (Rendered after EndMode3D)
        DrawCircle(screenWidth / 2, screenHeight / 2, 3, RAYWHITE); // Crosshair
        DrawRectangle(10, 10, 220, 70, Fade(BLACK, 0.6f));
        DrawText(TextFormat("SCORE: %04d", score), 25, 20, 20, GREEN);
        DrawText(TextFormat("REMAINING: %d/%d", MAX_ITEMS - (score / 100), MAX_ITEMS), 25, 45, 18, WHITE);

        if (score == MAX_ITEMS * 100)
        {
            DrawText("ISLAND CLEARED!", screenWidth / 2 - 160, screenHeight / 2 - 50, 36, YELLOW);
        }
        EndDrawing();
    }

    // 4. UNLOAD
    CloseWindow();
    return 0;
}