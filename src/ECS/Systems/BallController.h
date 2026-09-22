#pragma once

#include "ECS/Managers/EntityManager.h"
#include "ECS/Managers/EventsManager.h"
#include <windef.h>

class BallController {
private:
  static void
  move(EntityManager &entityManager, EventsManager &eventsManager, EntityID ballID);
  static void compute_bounce(
      EntityManager &entityManager, EventsManager &eventsManager, EntityID ballID
  );

public:
  static void process(EventsManager &eventsManager, EntityManager &entityManager);
  static EntityID getUnavailableBall(EntityManager &entityManager);
};