#include <raylib.h>

#include <algorithm>
#include <cmath>

namespace
{
constexpr int screenWidth = 800;
constexpr int screenHeight = 600;
constexpr float paddleWidth = 14.0f;
constexpr float paddleHeight = 112.0f;
constexpr float paddleSpeed = 460.0f;
constexpr float maxBallSpeed = 700.0f;

const Color background = {12, 18, 38, 255};
const Color courtGreen = {18, 30, 55, 255};
const Color dividerColor = {91, 112, 150, 100};
const Color leftColor = {72, 220, 190, 255};
const Color rightColor = {255, 190, 80, 255};

struct Paddle
{
    Rectangle bounds;
    Color color;
};

struct Ball
{
    Vector2 position;
    Vector2 velocity;
    float radius;
    float serveTimer;
    float serveDirection;
};

void KeepPaddleOnScreen(Paddle& paddle)
{
    paddle.bounds.y = std::clamp(paddle.bounds.y, 0.0f, screenHeight - paddle.bounds.height);
}

void ResetBall(Ball& ball, float direction)
{
    ball.position = {screenWidth / 2.0f, screenHeight / 2.0f};
    ball.velocity = {0.0f, 0.0f};
    ball.serveTimer = 0.8f;
    ball.serveDirection = direction;
}

void ServeBall(Ball& ball)
{
    const float speed = 390.0f;
    const float verticalSpeed = static_cast<float>(GetRandomValue(-180, 180));
    ball.velocity = {ball.serveDirection * speed, verticalSpeed};
}

void BounceOffPaddle(Ball& ball, const Paddle& paddle, bool movingRight)
{
    const float hitPosition = std::clamp(
        (ball.position.y - (paddle.bounds.y + paddle.bounds.height / 2.0f)) /
            (paddle.bounds.height / 2.0f),
        -1.0f,
        1.0f);
    const float currentSpeed = std::sqrt(
        ball.velocity.x * ball.velocity.x + ball.velocity.y * ball.velocity.y);
    const float newSpeed = std::min(currentSpeed * 1.04f, maxBallSpeed);
    const float angle = hitPosition * 1.04719755f;
    const float horizontalSpeed = newSpeed * std::cos(angle);

    ball.velocity.x = movingRight ? horizontalSpeed : -horizontalSpeed;
    ball.velocity.y = newSpeed * std::sin(angle);

    if (movingRight)
    {
        ball.position.x = paddle.bounds.x + paddle.bounds.width + ball.radius;
    }
    else
    {
        ball.position.x = paddle.bounds.x - ball.radius;
    }
}

void DrawCourt()
{
    ClearBackground(background);
    DrawRectangle(0, 0, screenWidth / 2, screenHeight, courtGreen);

    for (int y = 16; y < screenHeight; y += 30)
    {
        DrawRectangle(screenWidth / 2 - 2, y, 4, 16, dividerColor);
    }

    DrawCircleLines(screenWidth / 2, screenHeight / 2, 88.0f, dividerColor);
    DrawCircle(screenWidth / 2, screenHeight / 2, 4.0f, dividerColor);
    DrawRectangleLinesEx(
        Rectangle{8.0f, 8.0f, screenWidth - 16.0f, screenHeight - 16.0f},
        2.0f,
        Color{91, 112, 150, 100});
}

void DrawPaddle(const Paddle& paddle)
{
    Rectangle shadow = paddle.bounds;
    shadow.x += 4.0f;
    shadow.y += 5.0f;
    DrawRectangleRounded(shadow, 0.7f, 8, Color{0, 0, 0, 80});
    DrawRectangleRounded(paddle.bounds, 0.7f, 8, paddle.color);
}

void DrawScore(int score, int centerX, const char* label, Color color)
{
    const int labelWidth = MeasureText(label, 16);
    DrawText(label, centerX - labelWidth / 2, 24, 16, color);

    const char* scoreText = TextFormat("%02i", score);
    const int scoreWidth = MeasureText(scoreText, 48);
    DrawText(scoreText, centerX - scoreWidth / 2, 44, 48, RAYWHITE);
}
} // namespace

int main()
{
    InitWindow(screenWidth, screenHeight, "NEON PONG");
    SetTargetFPS(60);

    Paddle leftPaddle = {
        {32.0f, screenHeight / 2.0f - paddleHeight / 2.0f, paddleWidth, paddleHeight},
        leftColor};
    Paddle rightPaddle = {
        {screenWidth - 32.0f - paddleWidth, screenHeight / 2.0f - paddleHeight / 2.0f,
         paddleWidth, paddleHeight},
        rightColor};
    Ball ball = {{0.0f, 0.0f}, {0.0f, 0.0f}, 11.0f, 0.0f, 1.0f};
    int leftScore = 0;
    int rightScore = 0;
    ResetBall(ball, 1.0f);

    while (!WindowShouldClose())
    {
        const float deltaTime = GetFrameTime();

        if (IsKeyDown(KEY_W))
        {
            leftPaddle.bounds.y -= paddleSpeed * deltaTime;
        }
        if (IsKeyDown(KEY_S))
        {
            leftPaddle.bounds.y += paddleSpeed * deltaTime;
        }
        if (IsKeyDown(KEY_UP))
        {
            rightPaddle.bounds.y -= paddleSpeed * deltaTime;
        }
        if (IsKeyDown(KEY_DOWN))
        {
            rightPaddle.bounds.y += paddleSpeed * deltaTime;
        }
        KeepPaddleOnScreen(leftPaddle);
        KeepPaddleOnScreen(rightPaddle);

        if (ball.serveTimer > 0.0f)
        {
            ball.serveTimer -= deltaTime;
            if (ball.serveTimer <= 0.0f)
            {
                ServeBall(ball);
            }
        }
        else
        {
            ball.position.x += ball.velocity.x * deltaTime;
            ball.position.y += ball.velocity.y * deltaTime;

            if (ball.position.y - ball.radius <= 8.0f)
            {
                ball.position.y = 8.0f + ball.radius;
                ball.velocity.y = std::abs(ball.velocity.y);
            }
            else if (ball.position.y + ball.radius >= screenHeight - 8.0f)
            {
                ball.position.y = screenHeight - 8.0f - ball.radius;
                ball.velocity.y = -std::abs(ball.velocity.y);
            }

            if (ball.velocity.x < 0.0f &&
                CheckCollisionCircleRec(ball.position, ball.radius, leftPaddle.bounds))
            {
                BounceOffPaddle(ball, leftPaddle, true);
            }
            else if (ball.velocity.x > 0.0f &&
                     CheckCollisionCircleRec(ball.position, ball.radius, rightPaddle.bounds))
            {
                BounceOffPaddle(ball, rightPaddle, false);
            }

            if (ball.position.x + ball.radius < 0.0f)
            {
                rightScore++;
                ResetBall(ball, -1.0f);
            }
            else if (ball.position.x - ball.radius > screenWidth)
            {
                leftScore++;
                ResetBall(ball, 1.0f);
            }
        }

        BeginDrawing();
        DrawCourt();
        DrawScore(leftScore, screenWidth / 4, "PLAYER 1", leftColor);
        DrawScore(rightScore, 3 * screenWidth / 4, "PLAYER 2", rightColor);

        DrawPaddle(leftPaddle);
        DrawPaddle(rightPaddle);
        DrawCircleV(
            Vector2{ball.position.x + 3.0f, ball.position.y + 4.0f},
            ball.radius + 3.0f,
            Color{0, 0, 0, 80});
        DrawCircleV(ball.position, ball.radius, Color{255, 246, 220, 255});
        DrawCircleV(ball.position, 4.0f, WHITE);

        if (ball.serveTimer > 0.0f)
        {
            DrawText("GET READY", screenWidth / 2 - MeasureText("GET READY", 18) / 2,
                     screenHeight / 2 + 112, 18, Color{190, 205, 230, 220});
        }

        DrawText("W / S", 24, screenHeight - 30, 14, leftColor);
        DrawText("UP / DOWN", screenWidth - 108, screenHeight - 30, 14, rightColor);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
