#include "ECS/Managers/EntityManager.h"
#include "ECS/Managers/EventsManager.h"

class MovementSystem {
public:
  static void
  process_moveEvents(EntityManager &entityManager, EventsManager &eventsManager);
};