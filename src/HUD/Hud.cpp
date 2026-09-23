#include "Hud.h"
#include "configs/settings.h"
#include "engine/engine.h"

unsigned int player_score = 0;
unsigned int enemy_score = 0;

void HUD::draw_center_line() {
  // Setup Buffer for the line

  unsigned int x = screen_width / 2;
  for (int i = 1; i < screen_height / 2; i++) {
    draw_rect(x, i * 2, 1, 1, Colors::WHITE, ' ');
  }
}

void HUD::draw_score() {
  draw_number(screen_width / 4, 1, player_score, Colors::WHITE_TEXT);
  draw_number(screen_width / 2 + screen_width / 4, 1, enemy_score, Colors::WHITE_TEXT);
}

void HUD::draw(EntityManager &entityManager) {
  HUD::draw_center_line();
  HUD::draw_score();
}

void HUD::increase_player_score() { player_score++; }

void HUD::increase_enemy_score() { enemy_score++; }
