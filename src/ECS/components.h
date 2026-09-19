#pragma once

#include <windows.h>

struct SpatialComponent {
  int x;
  int y;
  int w;
  int h;
};

struct RenderComponent {
  WORD color;
  char letter = ' ';
};

struct VelocityComponent {
  int moveSpeed;
  int dx;
  int dy;
};

struct PlayerTag {};
struct BallTag {};
struct EnemyTag {};
