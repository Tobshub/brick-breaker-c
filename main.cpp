#include "brick-breaker.h"
#include "raylib.h"
#include <cstdlib>

int main() {

  const int WINDOW_WIDTH = 800;
  const int WINDOW_HEIGHT = 600;

  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Brick Breaker");
  InitAudioDevice();

  Sound blip = LoadSound("retro-blip.mp3");

  SetTargetFPS(60);

  bool paused = false;
  int lives = 3;
  bool has_won = false;

  Circle BALL = {.position = {WINDOW_WIDTH / 2.f,
                              WINDOW_HEIGHT / 2.f + WINDOW_HEIGHT / 4.f},
                 .radius = 10.f};
  Vector2 ball_direction = {Random_Ball_X(), -1};
  int ball_speed = 5;

  Rectangle paddle = {WINDOW_WIDTH / 2.f, WINDOW_HEIGHT - 50.f, 150.f, 20.f};
  int paddle_speed = ball_speed + 2;

  const float BRICK_SIZE = 40.f;
  int cols = 12;
  BrickContainer brick_container = {
      .rows = 3,
      .cols = cols,
      .start = {WINDOW_WIDTH / 2.f - (cols * BRICK_SIZE / 2.f) - BRICK_SIZE,
                10}};
  const int BRICK_BORDER_SIZE = 1;

  // weird declaration to prevent compiler error
  Brick **bricks;
  bricks = new Brick *[brick_container.rows];
  for (int i = 0; i < brick_container.rows; i++) {
    bricks[i] = new Brick[brick_container.cols];
  }

  Build_Bricks_Conatiner(brick_container, bricks, BRICK_SIZE);

  while (!WindowShouldClose()) {

    if (IsKeyPressed(KEY_SPACE)) {
      if (has_won || lives < 0) {
        BALL.position = {WINDOW_WIDTH / 2.f,
                         WINDOW_HEIGHT / 2.f + WINDOW_HEIGHT / 4.f};
        ball_direction = {Random_Ball_X(), -1};
        lives = 3;
        has_won = false;
        Build_Bricks_Conatiner(brick_container, bricks, BRICK_SIZE);
      } else {
        paused = !paused;
      }
    }

    if (!paused && lives >= 0 && !has_won) {
      if (IsKeyPressed(KEY_LEFT) || IsKeyDown(KEY_LEFT)) {
        paddle.x -= paddle_speed;
      }
      if (IsKeyPressed(KEY_RIGHT) || IsKeyDown(KEY_RIGHT)) {
        paddle.x += paddle_speed;
      }

      BALL.position.x += ball_direction.x * ball_speed;
      BALL.position.y += ball_direction.y * ball_speed;

      for (int row = 0; row < brick_container.rows; row++) {
        for (int col = 0; col < brick_container.cols; col++) {
          if (bricks[row][col].collideable &&
              CheckCollisionCircleRec(BALL.position, BALL.radius,
                                      bricks[row][col].rect)) {
            int collision_side =
                CircleRectCollision(BALL, bricks[row][col].rect);
            if (collision_side != 0) {
              bricks[row][col].collideable = false;
              if (collision_side == -1) {
                ball_direction.x *= -1;
              } else if (collision_side == 1) {
                ball_direction.y *= -1;
              }
              PlaySound(blip);
            }
          }
        }
      }

      if (BALL.position.x >= (WINDOW_WIDTH - BALL.radius) ||
          BALL.position.x <= BALL.radius) {
        ball_direction.x *= -1;
        PlaySound(blip);
      }

      if (CheckCollisionCircleRec(BALL.position, BALL.radius, paddle)) {
        ball_direction.y = -1;
        PlaySound(blip);
      }
      if (BALL.position.y <= BALL.radius) {
        ball_direction.y *= -1;
        PlaySound(blip);
      } else if (BALL.position.y >= (WINDOW_HEIGHT - BALL.radius)) {
        ball_direction = {Random_Ball_X(), -1};
        BALL.position.x = WINDOW_WIDTH / 2.f;
        BALL.position.y = WINDOW_HEIGHT / 2.f + WINDOW_HEIGHT / 4.f;
        lives -= 1;
      }
    }

    BeginDrawing();
    ClearBackground(RAYWHITE);

    if (!paused && lives >= 0 && !has_won)
      DrawText(TextFormat("Lives: %i", lives), 5, 5, 30, RED);

    DrawCircleV(BALL.position, BALL.radius, RED);
    DrawRectangleRounded(paddle, .8f, 0, BLUE);

    has_won = true;

    for (int row = 0; row < brick_container.rows; row++) {
      for (int col = 0; col < brick_container.cols; col++) {
        if (bricks[row][col].collideable) {
          DrawRectangleRec(bricks[row][col].rect, GREEN);
          DrawRectangleLinesEx(bricks[row][col].rect, BRICK_BORDER_SIZE, BLACK);
          has_won = false;
        }
      }
    }

    if (has_won) {
      DrawText("YOU WIN", 5, 5, 30, GREEN);
    } else if (lives < 0) {
      DrawText("GAME OVER", 5, 5, 30, RED);
    } else if (paused) {
      DrawText("PAUSED", 5, 5, 30, GRAY);
    }

    EndDrawing();
  }

  UnloadSound(blip);

  CloseAudioDevice();
  CloseWindow();

  return 0;
}
