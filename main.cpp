#include "ECS/components.h"

#include "ECS/Managers/EntityManager.h"
#include "ECS/Managers/EventsManager.h"

#include "ECS/Systems/AIController.h"
#include "ECS/Systems/BallController.h"
#include "ECS/Systems/CollisionSystem.h"
#include "ECS/Systems/InputSystem.h"
#include "ECS/Systems/MovementSystem.h"
#include "ECS/Systems/PlayerController.h"
#include "ECS/Systems/RenderingSystem.h"
#include "HUD/Hud.h"

#include "Factories.h"
#include "configs/settings.h"
#include "engine/engine.h"

#include <random>
#include <synchapi.h>

bool appRunning = true;

EntityManager entityManager;
EventsManager eventsManager;

void draw() {
  clear_console();
  RenderingSystem::process(entityManager);
  HUD::draw(entityManager);
  render_frame();
}

POINT get_random_direction() {
  POINT direction;
  // 1. Obtain a random seed from the hardware
  static std::random_device rd;

  // 2. Initialize the standard Mersenne Twister engine with the seed
  static std::mt19937 gen(rd());

  // 3. Define the distribution range [inclusive, inclusive]
  static std::uniform_int_distribution<> distr(-1, 1);
  ;
  while (true) {
    direction.x = distr(gen);
    direction.y = distr(gen);

    if (direction.x == 0 || direction.y == 0) {
      continue;
    } else {
      break;
    }
  }

  return direction;
}

void spawn_ball() {
  create_ball(
      entityManager,
      screen_width / 2,
      screen_height / 2,
      Colors::WHITE_TEXT,
      get_random_direction()
  );
}

void update() {
  eventsManager.process();
  InputSystem::process_events(eventsManager);

  PlayerController::process(entityManager, eventsManager);
  AIController::process(eventsManager, entityManager);

  CollisionSystem::process(entityManager, eventsManager);
  BallController::process(eventsManager, entityManager);

  EntityID lostBall = BallController::getUnavailableBall(entityManager);

  if (lostBall != entityManager.INVALID_ENTITY) {
    SpatialComponent ballSpatial = entityManager.spatialComponents[lostBall];

    entityManager.DeleteEntity(lostBall); // To ensure the ball out of bounds is deleted
    spawn_ball();

    if (ballSpatial.x < 0) {
      HUD::increase_enemy_score();
    } else {
      HUD::increase_player_score();
    }
  }

  MovementSystem::process_moveEvents(entityManager, eventsManager);
}

void setup() {
  EntityID playerID = create_pad(
      entityManager,
      2,
      (screen_height - padheight) / 2,
      padWidth,
      padheight,
      Colors::WHITE
  );

  entityManager.setPlayerID(playerID);

  EntityID enemyPad = create_pad(
      entityManager,
      screen_width - padWidth - 2,
      (screen_height - padheight) / 2,
      padWidth,
      padheight,
      Colors::WHITE
  );
  entityManager.AddComponent(enemyPad, EnemyTag{});

  spawn_ball();
  setup_console();
}

int main() {
  setup();
  while (appRunning) {
    draw();
    update();
    Sleep(60);
  }
}