#include "BallController.h"
#include "ECS/Managers/EntityManager.h"
#include "ECS/Managers/EventsManager.h"

void BallController::process(
    EventsManager &eventsManager, EntityManager &entityManager
) {
  for (auto &[ballID, BallTag] : entityManager.ballTags) {
    if (entityManager.velocityComponents.count(ballID)) {
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
