#pragma once
#include "ECS/Managers/EventsManager.h"
#include <windows.h>

class PlayerController {
public:
  static void
  process_movement(EventsManager &eventsManager, EntityID playerID, WORD pressedKey);
  static void process(EntityManager &entityManager, EventsManager &eventsManager);
};