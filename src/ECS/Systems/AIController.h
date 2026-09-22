#include "ECS/Managers/EntityManager.h"
#include "ECS/Managers/EventsManager.h"

class AIController {
private:
  static EntityID getClosestBall(EntityManager &entityManager, EntityID padID);
  static void followBall(
      EventsManager &eventManager,
      EntityManager &entityManager,
      EntityID padID,
      EntityID ballID
  );

public:
  static void process(EventsManager &eventsManager, EntityManager &entityManager);
};