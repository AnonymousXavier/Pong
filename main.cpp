#include "ECS/Managers/EntityManager.h"
#include "ECS/Managers/EventsManager.h"
#include "ECS/Systems/BallController.h"
#include "ECS/Systems/CollisionSystem.h"
#include "ECS/Systems/InputSystem.h"
#include "ECS/Systems/MovementSystem.h"
#include "ECS/Systems/PlayerController.h"
#include "ECS/Systems/RenderingSystem.h"
#include "ECS/components.h"
#include "Factories.h"
#include "configs/settings.h"
#include "engine/engine.h"
#include <synchapi.h>

bool appRunning = true;

EntityManager entityManager;
EventsManager eventsManager;

void draw() {
  clear_console();
  RenderingSystem::process(entityManager);
  render_frame();
}

void update() {
  eventsManager.process();
  InputSystem::process_events(eventsManager);

  PlayerController::process(entityManager, eventsManager);
  CollisionSystem::process(entityManager, eventsManager);
  BallController::process(eventsManager, entityManager);

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
  create_ball(
      entityManager, screen_width / 2, screen_height / 2, Colors::WHITE_TEXT, {-1, -1}
  );

  EntityID enemyPad = create_pad(
      entityManager,
      screen_width - padWidth - 2,
      (screen_height - padheight) / 2,
      padWidth,
      padheight,
      Colors::WHITE
  );
  entityManager.AddComponent(enemyPad, EnemyTag{});
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