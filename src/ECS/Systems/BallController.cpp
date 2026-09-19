#include "BallController.h"
#include "ECS/Managers/EntityManager.h"
#include "ECS/Managers/EventsManager.h"
#include "ECS/components.h"
#include "configs/settings.h"

void BallController::process(
    EventsManager &eventsManager, EntityManager &entityManager
) {
  for (auto &[ballID, BallTag] : entityManager.ballTags) {
    if (entityManager.velocityComponents.count(ballID)) {
      BallController::compute_bounce(entityManager, eventsManager, ballID);
      BallController::move(entityManager, eventsManager, ballID);
    }
  }
}

void BallController::move(
    EntityManager &entityManager, EventsManager &eventsManager, EntityID ballID
) {
  // Send event to move the ball
  MoveEvent moveEvent;

  VelocityComponent velComp = entityManager.velocityComponents[ballID];
  moveEvent.id = ballID;
  moveEvent.dx = velComp.dx;
  moveEvent.dy = velComp.dy;
  moveEvent.moveSpeed = velComp.moveSpeed;

  eventsManager.AddEvent(moveEvent);
}

void BallController::compute_bounce(
    EntityManager &entityManager, EventsManager &eventsManager, EntityID ballID
) {
  if (entityManager.spatialComponents.count(ballID)) {
    SpatialComponent spatialComp = entityManager.spatialComponents[ballID];
    VelocityComponent &velocityComp = entityManager.velocityComponents[ballID];

    if (spatialComp.y <= 0) {
      velocityComp.dy = 1;
    } else if (spatialComp.y >= screen_height - spatialComp.h) {
      velocityComp.dy = -1;
    }
  }
}