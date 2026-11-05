#include <bits/stdc++.h>
#include <raylib.h>
using namespace std;

Color green = Color{38, 185, 154, 255};
Color Darkgreen = Color{20, 160, 133, 255};
Color Lightgreen = Color{129, 204, 184, 255};
Color Yellow = Color{243, 213, 91, 255};

int playerScore = 0;
int cpuScore = 0;
class Ball
{

public:
    float x, y;
    int speed_x, speed_y;
    int radius;

    void Draw()
    {
        DrawCircle(x, y, radius, Yellow);
    }
    void update()
    {
        x += speed_x;
        y += speed_y;
        if (y + radius >= GetScreenHeight() || y - radius <= 0)
        {
            speed_y *= -1;
        }
        if (x + radius >= GetScreenWidth()) // cpu wins
        {
            cpuScore++;
            ResetBall();
        }
        if (x - radius <= 0)
        {
            playerScore++;
            ResetBall();
        }
    }
    void ResetBall()
    {
        x = GetScreenWidth() / 2;
        y = GetScreenHeight() / 2;

        int speedChoice[2] = {1, -1};
        speed_x *= speedChoice[GetRandomValue(0, 1)];
        speed_y *= speedChoice[GetRandomValue(0, 1)];
    }
};

class Paddle
{
protected:
    void LimitMov()
    {
        if (y <= 0)
        {
            y = 0;
        }
        if (y + height >= GetScreenHeight())
        {
            y = GetScreenHeight() - height;
        }
    }

public:
    float x, y;
    float width, height;
    int speed;
    void Draw()
    {
        DrawRectangleRounded(Rectangle{x,y,width,height},0.8,0,WHITE);
    }
    void update()
    {
        if (IsKeyDown(KEY_UP))
        {
            y = y - speed;
        }
        if (IsKeyDown(KEY_DOWN))
        {
            y = y + speed;
        }
        LimitMov();
    }
};
class CpuPaddle : public Paddle
{
public:
    void update(int ballY)
    {
        if (y + height / 2 > ballY)
        {
            y = y - speed;
        }
        if (y + height / 2 <= ballY)
        {
            y = y + speed;
        }
        LimitMov();
    }
};

Ball ball;
Paddle p1;
CpuPaddle cpu;

int main()
{
    cout << "Starting the game...\n";
    const int screen_height = 600;
    const int screen_width = 800;
    InitWindow(screen_width, screen_height, "Ping Pong"); // creating window
    SetTargetFPS(60);

    ball.radius = 12;
    ball.x = screen_width / 2;
    ball.y = screen_height / 2;
    ball.speed_x = 7;
    ball.speed_y = 7;

    p1.width = 12;
    p1.height = 100;
    p1.x = screen_width - p1.width - 10;
    p1.y = screen_height / 2 - p1.height / 2;
    p1.speed = 6;

    cpu.height = 100;
    cpu.width = 12;
    cpu.x = 10;
    cpu.y = screen_height / 2 - cpu.height / 2;
    cpu.speed = 6;

    while (WindowShouldClose() == false) // GameLoop
    {
        BeginDrawing();
        // Update
        ball.update();
        p1.update();
        cpu.update(ball.y);

        if (CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{p1.x, p1.y, p1.width, p1.height}))
        {

            ball.speed_x *= -1;
        }
        if (CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{cpu.x, cpu.y, cpu.width, cpu.height}))
        {
            ball.speed_x *= -1;
        }

        // Draw
        ClearBackground(Darkgreen);
        DrawRectangle(screen_width/2,0,screen_width/2,screen_height,green);
        DrawCircle(screen_width/2,screen_height/2,150,Lightgreen);
        DrawLine(screen_width / 2, 0, screen_width / 2, screen_height, WHITE);
        ball.Draw();
        cpu.Draw();
        p1.Draw();
        // Show Score
        DrawText(TextFormat("%i", cpuScore), screen_width / 4 - 20, 20, 80, WHITE);
        DrawText(TextFormat("%i", playerScore), 3 * screen_width / 4 - 20, 20, 80, WHITE);

        EndDrawing();
    }

    CloseWindow(); // closing window
    return 0;
}