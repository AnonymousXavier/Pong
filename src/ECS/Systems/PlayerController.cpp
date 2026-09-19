#include "PlayerController.h"
#include "../../configs/settings.h"
#include <windows.h>

void PlayerController::process(
    EntityManager &entityManager, EventsManager &eventsManager
) {

  for (const GameEvent &gameEvent : eventsManager.getEvent()) {
    switch (gameEvent.type) {
    case EventType::MoveIntent:
      break;
    case EventType::keyPress:
      PlayerController::process_movement(
          eventsManager, entityManager.getPlayerID(), gameEvent.key.keyCode
      );
      break;
    }
  }
}

void PlayerController::process_movement(
    EventsManager &eventsManager, EntityID playerID, WORD pressedKey
) {
  if (pressedKey != VK_UP && pressedKey != VK_DOWN) {
    return;
  }

  MoveEvent moveEvent;
  moveEvent.id = playerID;
  moveEvent.moveSpeed = padMoveSpeed;

  if (pressedKey == VK_DOWN) {
    moveEvent.dx = 0;
    moveEvent.dy = 1;
  } else if (pressedKey == VK_UP) {
    moveEvent.dx = 0;
    moveEvent.dy = -1;
  }

  eventsManager.AddEvent(moveEvent);
}