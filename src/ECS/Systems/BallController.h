#pragma once

#include "ECS/Managers/EntityManager.h"
#include "ECS/Managers/EventsManager.h"
#include <windef.h>

class BallController {
public:
  static void process(EventsManager &eventsManager, EntityManager &entityManager);
  static void move(EntityManager &entityManager, EventsManager &eventsManager, EntityID ballID);
};