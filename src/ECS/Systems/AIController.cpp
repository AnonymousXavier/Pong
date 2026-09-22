#include "AIController.h"
#include "ECS/Managers/EntityManager.h"
#include "ECS/Managers/EventsManager.h"
#include "configs/settings.h"

void AIController::process(EventsManager &eventsManager, EntityManager &entityManager) {
  for (auto &[padID, _] : entityManager.enemyTags) {
    if (entityManager.HasSpatialComponent(padID)) {
      EntityID ballID = AIController::getClosestBall(entityManager, padID);
      if (ballID != -1) { // We have a ball, Track it
        AIController::followBall(eventsManager, entityManager, padID, ballID);
      }
    }
  }
}

EntityID AIController::getClosestBall(EntityManager &entityManager, EntityID padID) {
  EntityID closestBallID = -1;
  int shortestDistance = screen_width;

  SpatialComponent padSpatial = entityManager.spatialComponents[padID];
  for (auto &[ballID, _] : entityManager.ballTags) {
    if (entityManager.HasSpatialComponent(ballID)) {
      SpatialComponent ballSpatial = entityManager.spatialComponents[ballID];

      int distance = padSpatial.x - ballSpatial.x;
      if (distance < shortestDistance) {
        distance = shortestDistance;
        closestBallID = ballID;
      }
    }
  }

  return closestBallID;
}

void AIController::followBall(
    EventsManager &eventManager,
    EntityManager &entityManager,
    EntityID padID,
    EntityID ballID
) {
  SpatialComponent padSpatial = entityManager.spatialComponents[padID];
  SpatialComponent ballSpatial = entityManager.spatialComponents[ballID];

  int pad_centerY = padSpatial.y + padSpatial.h / 2;
  int dy;

  // Only follow if past the halfway mark
  if (ballSpatial.x < screen_width / 2) {
    // Return to the center of the screen

    int screen_centerY = screen_height / 2;
    dy = pad_centerY > screen_centerY ? -1 : screen_centerY == pad_centerY ? 0 : 1;

  } else {
    int ball_centerY = ballSpatial.y + ballSpatial.h / 2;

    dy = pad_centerY > ball_centerY ? -1 : ball_centerY == pad_centerY ? 0 : 1;
  }

  MoveEvent moveEvent;
  moveEvent.id = padID;
  moveEvent.dx = 0;
  moveEvent.dy = dy;
  moveEvent.moveSpeed = padMoveSpeed;

  eventManager.AddEvent(moveEvent);
}