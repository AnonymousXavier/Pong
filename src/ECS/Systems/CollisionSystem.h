#include "ECS/Managers/EntityManager.h"
#include "ECS/Managers/EventsManager.h"

class CollisionSystem {
public:
  static void process(EntityManager &entityManager, EventsManager &eventsManager);
  static void
  record_collision(EventsManager &eventsManager, EntityID ballID, EntityID padID);
  static bool
  is_colliding(SpatialComponent spatialComp1, SpatialComponent spatialComp2);
  static void handle_collision(
      EntityManager &entityManager,
      EventsManager &eventsManager,
      EntityID ballID,
      EntityID otherID
  );
};