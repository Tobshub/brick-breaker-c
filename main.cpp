#include "raylib.h"

struct Circle {
  Vector2 position;
  float radius;
};

// only use when a collision is detected
int CircleRectCollision(Circle &circle, Rectangle &rect) {

  // Check if the circle collides with the top or bottom edges of the rectangle
  if ((circle.position.y + circle.radius >= rect.y &&
       circle.position.y + circle.radius <=
           rect.y + rect.height) || // Circle collides with the top edge
      (circle.position.y - circle.radius >= rect.y &&
       circle.position.y - circle.radius <=
           rect.y + rect.height)) { // Circle collides with the bottom edge
    return 1;
  }

  // Check if the circle collides with the left or right edges of the rectangle
  if ((circle.position.x + circle.radius >= rect.x &&
       circle.position.x + circle.radius <=
           rect.x + rect.width) || // Circle collides with the left edge
      (circle.position.x - circle.radius >= rect.x &&
       circle.position.x - circle.radius <=
           rect.x + rect.width)) { // Circle collides with the right edge
    return -1;
  }
  return 0; // No collision
}

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

  Circle BALL = {.position = {WINDOW_WIDTH / 2.f,
                              WINDOW_HEIGHT / 2.f + WINDOW_HEIGHT / 4.f},
                 .radius = 10.f};
  Vector2 ball_direction = {1, -1};
  int ball_speed = 8;

  Rectangle paddle = {WINDOW_WIDTH / 2.f, WINDOW_HEIGHT - 50.f, 150.f, 20.f};
  int paddle_speed = 10;

  bool paused = false;

  const int BRICK_SIZE = 40;
  int cols = 15;
  BrickContainer brick_container = {
      .rows = 3,
      .cols = cols,
      .start = {WINDOW_WIDTH / 2.f - (cols * BRICK_SIZE / 2.f) - BRICK_SIZE,
                10}};
  const int BRICK_BORDER_SIZE = 1;

  Brick bricks[brick_container.rows][brick_container.cols];

  for (int row = 0; row < brick_container.rows; row++) {
    for (int col = 0; col < brick_container.cols; col++) {
      float x = (float)(col + 1) * BRICK_SIZE + brick_container.start.x;
      float y = (float)(row + 1) * BRICK_SIZE + brick_container.start.y;
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
            }
          }
        }
      }

      if (BALL.position.x >= (WINDOW_WIDTH - BALL.radius) ||
          BALL.position.x <= BALL.radius) {
        ball_direction.x *= -1;
      }

      if (CheckCollisionCircleRec(BALL.position, BALL.radius, paddle)) {
        ball_direction.y = -1;
      }
      if (BALL.position.y >= (WINDOW_HEIGHT - BALL.radius) ||
          BALL.position.y <= BALL.radius) {
        ball_direction.y *= -1;
      }
    }

    BeginDrawing();
    ClearBackground(RAYWHITE);

    DrawCircleV(BALL.position, BALL.radius, RED);
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
