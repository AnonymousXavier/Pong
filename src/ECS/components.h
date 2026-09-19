#pragma once

#include <windows.h>

struct SpatialComponent {
  unsigned int x;
  unsigned int y;
  unsigned int w;
  unsigned int h;
};

struct RenderComponent {
  WORD color;
  char letter = ' ';
};

struct VelocityComponent {
  unsigned int moveSpeed;
  int dx;
  int dy;
};

struct PlayerTag {};
struct BallTag {};
struct EnemyTag {};
