#include "CollisionSystem.h"
#include "ECS/Managers/EntityManager.h"

void CollisionSystem::process(
    EntityManager &entityManager, EventsManager &eventsManager
) {
  for (auto &[ballID, ballTag] : entityManager.ballTags) {
    CollisionSystem::handle_collision(
        entityManager, eventsManager, ballID, entityManager.getPlayerID()
    );

    for (auto &[enemyID, enemyTag] : entityManager.enemyTags) {
      CollisionSystem::handle_collision(entityManager, eventsManager, ballID, enemyID);
    }
  }
}

void CollisionSystem::handle_collision(
    EntityManager &entityManager,
    EventsManager &eventsManager,
    EntityID ballID,
    EntityID otherID
) {
  if (entityManager.HasSpatialComponent(ballID) &&
      entityManager.HasSpatialComponent(otherID)) {
    SpatialComponent ballSpatial = entityManager.spatialComponents[ballID];
    SpatialComponent enemySpatial = entityManager.spatialComponents[otherID];
    if (CollisionSystem::is_colliding(ballSpatial, enemySpatial)) {
      CollisionSystem::record_collision(eventsManager, ballID, otherID);
    }
  }
}

void CollisionSystem::record_collision(
    EventsManager &eventsManager, EntityID ballID, EntityID padID
) {
  CollisionEvent collisionEvent;
  collisionEvent.ballID = ballID;
  collisionEvent.padID = padID;

  eventsManager.AddEvent(collisionEvent);
}

bool CollisionSystem::is_colliding(
    SpatialComponent spatialComp1, SpatialComponent spatialComp2
) {
  bool overlaps_horizontally = spatialComp1.x < spatialComp2.x + spatialComp2.w &&
                               spatialComp1.x + spatialComp1.w > spatialComp2.x;

  bool overlaps_vertically = spatialComp1.y < spatialComp2.y + spatialComp2.h &&
                             spatialComp1.y + spatialComp1.h > spatialComp2.y;

  return overlaps_horizontally && overlaps_vertically;
}