#include "ECS/Managers/EntityManager.h"

class HUD {
private:
  static void draw_center_line();
  static void draw_score();

public:
  static void draw(EntityManager &entityManager);
  static void increase_player_score();
  static void increase_enemy_score();
};