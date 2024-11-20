#include "raylib.h"

#define BALL_RADIUS 10
#define PADDLE_WIDTH 100
#define PADDLE_HEIGHT 10
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 450
#define MAX_CHANCES 3

typedef struct Ball {
    Vector2 position;
    Vector2 speed;
    float radius;
} Ball;

typedef struct Paddle {
    Vector2 position;
    float width;
    float height;
    float speed;
} Paddle;

int main(void)
{
    // Initialize window, ball, paddle, and chances
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Bouncing Ball Game with Paddle and Chances");

    Ball ball = {0};
    ball.radius = BALL_RADIUS;
    ball.position = (Vector2){SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};
    ball.speed = (Vector2){4.0f, 4.0f};

    Paddle paddle = {0};
    paddle.position = (Vector2){SCREEN_WIDTH / 2 - PADDLE_WIDTH / 2, SCREEN_HEIGHT - 40}; // Near bottom
    paddle.width = PADDLE_WIDTH;
    paddle.height = PADDLE_HEIGHT;
    paddle.speed = 8.0f;

    int chances = MAX_CHANCES; // Player starts with 3 chances

    SetTargetFPS(60);  // Set FPS to 60

    bool gameOver = false;
    bool gameStarted = false;

    // Red line (wall) position
    float wallY = 50;

    while (!WindowShouldClose())  // Main game loop
    {
        if (!gameStarted) {
            // Display start screen
            BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawText("Bouncing Ball Game", SCREEN_WIDTH / 2 - MeasureText("Bouncing Ball Game", 40) / 2, SCREEN_HEIGHT / 2 - 60, 40, DARKBLUE);
            DrawText("Press ENTER to start", SCREEN_WIDTH / 2 - MeasureText("Press ENTER to start", 20) / 2, SCREEN_HEIGHT / 2, 20, BLACK);
            EndDrawing();

            // Check for start input
            if (IsKeyPressed(KEY_ENTER)) {
                gameStarted = true;
            }
        } else {
            // Game logic when started
            // Update ball position
            ball.position.x += ball.speed.x;
            ball.position.y += ball.speed.y;

            // Ball bounce logic (screen boundaries)
            if (ball.position.x - ball.radius <= 0 || ball.position.x + ball.radius >= SCREEN_WIDTH) 
                ball.speed.x *= -1;  // Reverse the ball's horizontal direction

            if (ball.position.y - ball.radius <= 0) 
                ball.speed.y *= -1;  // Reverse the ball's vertical direction (top edge)

            // Ball and paddle collision (check if ball hits the paddle)
            if (ball.position.y + ball.radius >= paddle.position.y &&
                ball.position.y - ball.radius <= paddle.position.y + paddle.height &&
                ball.position.x + ball.radius >= paddle.position.x &&
                ball.position.x - ball.radius <= paddle.position.x + paddle.width) {
                ball.speed.y *= -1;  // Reverse ball's vertical direction
            }

            // Ball falls below the screen (game over)
            if (ball.position.y + ball.radius >= SCREEN_HEIGHT) {
                chances--; // Decrease chances
                ball.position = (Vector2){SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2}; // Reset ball position
                if (chances <= 0) {
                    gameOver = true; // No more chances left
                }
            }

            // Ball bounce off the red wall (if the ball reaches the red line)
            if (ball.position.y - ball.radius <= wallY) {
                ball.speed.y *= -1;  // Reverse ball's vertical direction when it hits the red line
            }

            // Paddle movement (using left and right arrow keys or A/D keys)
            if (IsKeyDown(KEY_LEFT) && paddle.position.x > 0) {
                paddle.position.x -= paddle.speed;
            }

            if (IsKeyDown(KEY_RIGHT) && paddle.position.x < SCREEN_WIDTH - paddle.width) {
                paddle.position.x += paddle.speed;
            }
        }

        // Draw everything
        BeginDrawing();
        ClearBackground(RAYWHITE);

        if (gameOver) {
            DrawText("GAME OVER", SCREEN_WIDTH / 2 - MeasureText("GAME OVER", 20) / 2, SCREEN_HEIGHT / 2 - 10, 20, RED);
        } else if (!gameStarted) {
            // Display start screen
            DrawText("Bouncing Ball Game", SCREEN_WIDTH / 2 - MeasureText("Bouncing Ball Game", 40) / 2, SCREEN_HEIGHT / 2 - 60, 40, DARKBLUE);
            DrawText("Press ENTER to start", SCREEN_WIDTH / 2 - MeasureText("Press ENTER to start", 20) / 2, SCREEN_HEIGHT / 2, 20, BLACK);
        } else {
            // Draw the red wall
            DrawLine(0, wallY, SCREEN_WIDTH, wallY, RED);  // Draw the red wall at y = 50

            // Draw the ball
            DrawCircleV(ball.position, ball.radius, MAROON);

            // Draw the paddle
            DrawRectangleV(paddle.position, (Vector2){paddle.width, paddle.height}, DARKBLUE);

            // Display the remaining chances
            DrawText(TextFormat("Chances: %d", chances), 10, 10, 20, BLACK); 
        }

        EndDrawing();
    }

    // De-Initialization
    CloseWindow(); // Close the window and OpenGL context

    return 0;
}
