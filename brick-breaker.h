#include "raylib.h"
#include <cstdlib>

struct Circle {
  Vector2 position;
  float radius;
};

struct Brick {
  Rectangle rect;
  bool collideable;
};

struct BrickContainer {
  int rows;
  int cols;
  Vector2 start;
};

void Build_Bricks_Conatiner(BrickContainer brick_container, Brick **bricks,
                            float BRICK_SIZE);

// generate a random non-zero float
float Random_NZ_Float(float min, float max);

#define Random_Ball_X() Random_NZ_Float(-1.f, 1.f)

// only use when a collision is detected;
// return 1 for top/bottom collision,
// return -1 for left/right collision.
int CircleRectCollision(Circle &circle, Rectangle &rect);
