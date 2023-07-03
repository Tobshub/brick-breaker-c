#include "raylib.h"

int main() {

  const int WINDOW_WIDTH = 800;
  const int WINDOW_HEIGHT = 480;

  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Brick Breaker");
  SetTargetFPS(60);

  Vector2 ball_position = {WINDOW_WIDTH / 2.f, WINDOW_HEIGHT / 2.f};
  Vector2 ball_direction = {1, 1};
  int ball_speed = 5;
  const int BALL_RADIUS = 10;

  Rectangle paddle = {WINDOW_WIDTH / 2.f, WINDOW_HEIGHT - 50.f, 150.f, 20.f};
  int paddle_speed = 5;

  bool paused = false;

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
      if (ball_position.y >= (WINDOW_HEIGHT - BALL_RADIUS) ||
          ball_position.y <= BALL_RADIUS) {
        ball_direction.y *= -1;
      }
    }

    BeginDrawing();
    ClearBackground(RAYWHITE);

    DrawCircleV(ball_position, BALL_RADIUS, RED);
    DrawRectangleRec(paddle, BLUE);

    if (paused) {
      DrawText("PAUSED", 5, 5, 30, GRAY);
    }

    EndDrawing();
  }

  CloseWindow();

  return 0;
}
