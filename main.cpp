#include "raylib.h"

struct Brick {
  Rectangle rect;
  bool collideable;
};
struct BrickContainer {
  int rows;
  int cols;
  Vector2 start;
};

int main() {

  const int WINDOW_WIDTH = 800;
  const int WINDOW_HEIGHT = 600;

  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Brick Breaker");
  SetTargetFPS(60);

  Vector2 ball_position = {WINDOW_WIDTH / 2.f, WINDOW_HEIGHT / 2.f};
  Vector2 ball_direction = {1, 1};
  int ball_speed = 5;
  const int BALL_RADIUS = 10;

  Rectangle paddle = {WINDOW_WIDTH / 2.f, WINDOW_HEIGHT - 50.f, 150.f, 20.f};
  int paddle_speed = 8;

  bool paused = false;

  BrickContainer brick_container = {.rows = 3, .cols = 10, .start = {10, 10}};
  const int BRICK_SIZE = 40;
  const int BRICK_BORDER_SIZE = 1;

  Brick bricks[brick_container.rows][brick_container.cols];

  for (int row = 0; row < brick_container.rows; row++) {
    for (int col = 0; col < brick_container.cols; col++) {
      float x = (float)(col + 1) * BRICK_SIZE;
      float y = (float)(row + 1) * BRICK_SIZE;
      bricks[row][col] = Brick{.rect = Rectangle{x, y, BRICK_SIZE, BRICK_SIZE},
                               .collideable = true};
    }
  }

  while (!WindowShouldClose()) {

    if (IsKeyPressed(KEY_SPACE)) {
      paused = !paused;
    }

    if (!paused) {
      if (IsKeyPressed(KEY_LEFT) || IsKeyDown(KEY_LEFT)) {
        paddle.x -= paddle_speed;
      }
      if (IsKeyPressed(KEY_RIGHT) || IsKeyDown(KEY_RIGHT)) {
        paddle.x += paddle_speed;
      }

      ball_position.x += ball_direction.x * ball_speed;
      ball_position.y += ball_direction.y * ball_speed;

      if (ball_position.x >= (WINDOW_WIDTH - BALL_RADIUS) ||
          ball_position.x <= BALL_RADIUS) {
        ball_direction.x *= -1;
      }

      if (CheckCollisionCircleRec(ball_position, BALL_RADIUS, paddle)) {
        ball_direction.y = -1;
      }
      if (ball_position.y >= (WINDOW_HEIGHT - BALL_RADIUS) ||
          ball_position.y <= BALL_RADIUS) {
        ball_direction.y *= -1;
      }
    }

    BeginDrawing();
    ClearBackground(RAYWHITE);

    DrawCircleV(ball_position, BALL_RADIUS, RED);
    DrawRectangleRec(paddle, BLUE);

    for (int row = 0; row < brick_container.rows; row++) {
      for (int col = 0; col < brick_container.cols; col++) {
        if (bricks[row][col].collideable) {
          DrawRectangleRec(bricks[row][col].rect, GREEN);
          DrawRectangleLinesEx(bricks[row][col].rect, BRICK_BORDER_SIZE, BLACK);
        }
      }
    }

    if (paused) {
      DrawText("PAUSED", 5, 5, 30, GRAY);
    }

    EndDrawing();
  }

  CloseWindow();

  return 0;
}
