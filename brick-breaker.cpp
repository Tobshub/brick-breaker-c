#include "brick-breaker.h"
#include "raylib.h"
#include <cstdlib>

void Build_Bricks_Conatiner(BrickContainer brick_container, Brick **bricks,
                            float BRICK_SIZE) {
  for (int row = 0; row < brick_container.rows; row++) {
    for (int col = 0; col < brick_container.cols; col++) {
      float x = (float)(col + 1) * BRICK_SIZE + brick_container.start.x;
      float y = (float)(row + 1) * BRICK_SIZE + brick_container.start.y;
      bricks[row][col] = Brick{.rect = Rectangle{x, y, BRICK_SIZE, BRICK_SIZE},
                               .collideable = true};
    }
  }
}

// generate a random non-zero float
float Random_NZ_Float(float min, float max) {
  float num = 0.f;
  while (num == 0.f) {
    num = min + (max - min) * ((float)rand() / (float)RAND_MAX);
  }
  return num;
}

// only use when a collision is detected;
// return 1 for top/bottom collision,
// return -1 for left/right collision.
int CircleRectCollision(Circle &circle, Rectangle &rect) {
  // Check if the circle collides with the top or bottom edges of the rectangle
  // Circle collides with the top edge
  if (circle.position.y < rect.y &&
      circle.position.y + circle.radius >= rect.y &&
      circle.position.y + circle.radius <= rect.y + rect.height) {
    return 1;
  }
  // Circle collides with the bottom edge
  if (circle.position.y > rect.y + rect.height &&
      circle.position.y - circle.radius >= rect.y + rect.height &&
      circle.position.y - circle.radius <= rect.y + rect.height * 2) {
    return 1;
  }

  // Check if the circle collides with the left or right edges of the rectangle
  // Circle collides with the left edge
  if (circle.position.x < rect.x &&
      circle.position.x + circle.radius >= rect.x &&
      circle.position.x + circle.radius <= rect.x + rect.width) {
    return -1;
  }
  // Circle collides with the right edge
  if (circle.position.x > rect.x &&
      circle.position.x - circle.radius >= rect.x &&
      circle.position.x - circle.radius <= rect.x + rect.width) {
    return -1;
  }
  return 0; // No collision
}
