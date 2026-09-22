#include "BallController.h"
#include "ECS/Managers/EntityManager.h"
#include "ECS/Managers/EventsManager.h"
#include "ECS/components.h"
#include "configs/Misc.h"
#include "configs/settings.h"
#include <vector>

void BallController::process(
    EventsManager &eventsManager, EntityManager &entityManager
) {

  std::vector<EntityID> collidedBalls;

  for (const GameEvent &gameEvent : eventsManager.getEvent()) {
    if (gameEvent.type == EventType::collisionEvent) {
      VelocityComponent &ballVelocity =
          entityManager.velocityComponents[gameEvent.collision.ballID];
      if (gameEvent.collision.padID == entityManager.getPlayerID()) {
        ballVelocity.dx = 1; // Is the player
      } else {
        ballVelocity.dx = -1; // Is an enemy
      }
      BallController::move(entityManager, eventsManager, gameEvent.collision.ballID);
      collidedBalls.push_back(gameEvent.collision.ballID);
    }
  }

  for (auto &[ballID, BallTag] : entityManager.ballTags) {
    if (entityManager.HasVelocityComponent(ballID)) {
      if (find(collidedBalls, ballID)) {
        continue;
      }
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

EntityID BallController::getUnavailableBall(EntityManager &entityManager) {
  for (auto &[ballID, BallTag] : entityManager.ballTags) {
    if (entityManager.HasSpatialComponent(ballID)) {
      SpatialComponent ballSpatial = entityManager.spatialComponents[ballID];
      if (ballSpatial.x < 0 || ballSpatial.x > screen_width || ballSpatial.y < 0 ||
          ballSpatial.y > screen_height) {
        return ballID;
      }
    }
  }
  return 0;
}