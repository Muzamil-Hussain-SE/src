#include <raylib.h>

const int screenWidth = 800;
const int screenHeight = 600;
const int paddleWidth = 14;
const int paddleHeight = 110;
const int ballRadius = 11;
const float paddleSpeed = 400.0f;

const Color backgroundColor = {12, 18, 38, 255};
const Color courtColor = {18, 30, 55, 255};
const Color lineColor = {91, 112, 150, 100};
const Color player1Color = {72, 220, 190, 255};
const Color player2Color = {255, 190, 80, 255};

void DrawCourt()
{
    ClearBackground(backgroundColor);
    DrawRectangle(0, 0, screenWidth / 2, screenHeight, courtColor);

    // Draw the dashed line in the middle of the court.
    for (int y = 16; y < screenHeight; y += 30)
    {
        DrawRectangle(screenWidth / 2 - 2, y, 4, 16, lineColor);
    }

    DrawCircleLines(screenWidth / 2, screenHeight / 2, 88, lineColor);
    DrawRectangleLines(8, 8, screenWidth - 16, screenHeight - 16, lineColor);
}

void DrawScore(int player1Score, int player2Score)
{
    DrawText("PLAYER 1", screenWidth / 4 - 48, 24, 16, player1Color);
    DrawText(TextFormat("%02i", player1Score), screenWidth / 4 - 30, 44, 48, RAYWHITE);

    DrawText("PLAYER 2", 3 * screenWidth / 4 - 48, 24, 16, player2Color);
    DrawText(TextFormat("%02i", player2Score), 3 * screenWidth / 4 - 30, 44, 48, RAYWHITE);
}

int main()
{
    InitWindow(screenWidth, screenHeight, "NEON PONG");
    SetTargetFPS(60);

    // A Rectangle stores a paddle's left position, top position, width, and height.
    Rectangle player1 = {32, screenHeight / 2 - paddleHeight / 2, paddleWidth, paddleHeight};
    Rectangle player2 = {
        screenWidth - 32 - paddleWidth,
        screenHeight / 2 - paddleHeight / 2,
        paddleWidth,
        paddleHeight};

    float ballX = screenWidth / 2.0f;
    float ballY = screenHeight / 2.0f;
    float ballSpeedX = 360.0f;
    float ballSpeedY = 220.0f;

    int player1Score = 0;
    int player2Score = 0;

    while (!WindowShouldClose())
    {
        // GetFrameTime keeps movement similar at different frame rates.
        float frameTime = GetFrameTime();

        // Move player 1 with W and S.
        if (IsKeyDown(KEY_W))
        {
            player1.y -= paddleSpeed * frameTime;
        }
        if (IsKeyDown(KEY_S))
        {
            player1.y += paddleSpeed * frameTime;
        }

        // Move player 2 with the up and down arrow keys.
        if (IsKeyDown(KEY_UP))
        {
            player2.y -= paddleSpeed * frameTime;
        }
        if (IsKeyDown(KEY_DOWN))
        {
            player2.y += paddleSpeed * frameTime;
        }

        // Keep both paddles inside the window.
        if (player1.y < 8)
        {
            player1.y = 8;
        }
        if (player1.y + paddleHeight > screenHeight - 8)
        {
            player1.y = screenHeight - paddleHeight - 8;
        }
        if (player2.y < 8)
        {
            player2.y = 8;
        }
        if (player2.y + paddleHeight > screenHeight - 8)
        {
            player2.y = screenHeight - paddleHeight - 8;
        }

        // Move the ball.
        ballX += ballSpeedX * frameTime;
        ballY += ballSpeedY * frameTime;

        // Bounce off the top and bottom edges.
        if (ballY - ballRadius < 8)
        {
            ballY = 8 + ballRadius;
            ballSpeedY = -ballSpeedY;
        }
        if (ballY + ballRadius > screenHeight - 8)
        {
            ballY = screenHeight - 8 - ballRadius;
            ballSpeedY = -ballSpeedY;
        }

        // Bounce off player 1's paddle.
        if (ballSpeedX < 0 &&
            CheckCollisionCircleRec(Vector2{ballX, ballY}, ballRadius, player1))
        {
            ballX = player1.x + paddleWidth + ballRadius;
            ballSpeedX = -ballSpeedX;
        }

        // Bounce off player 2's paddle.
        if (ballSpeedX > 0 &&
            CheckCollisionCircleRec(Vector2{ballX, ballY}, ballRadius, player2))
        {
            ballX = player2.x - ballRadius;
            ballSpeedX = -ballSpeedX;
        }

        // If the ball goes past player 1, player 2 gets a point.
        if (ballX + ballRadius < 0)
        {
            player2Score++;
            ballX = screenWidth / 2.0f;
            ballY = screenHeight / 2.0f;
            ballSpeedX = -360.0f;
            ballSpeedY = 220.0f;
        }

        // If the ball goes past player 2, player 1 gets a point.
        if (ballX - ballRadius > screenWidth)
        {
            player1Score++;
            ballX = screenWidth / 2.0f;
            ballY = screenHeight / 2.0f;
            ballSpeedX = 360.0f;
            ballSpeedY = 220.0f;
        }

        BeginDrawing();
        DrawCourt();
        DrawScore(player1Score, player2Score);

        DrawRectangleRec(player1, player1Color);
        DrawRectangleRec(player2, player2Color);
        DrawCircle(ballX + 3, ballY + 4, ballRadius + 3, Color{0, 0, 0, 80});
        DrawCircle(ballX, ballY, ballRadius, RAYWHITE);

        DrawText("W / S", 24, screenHeight - 30, 14, player1Color);
        DrawText("UP / DOWN", screenWidth - 108, screenHeight - 30, 14, player2Color);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
