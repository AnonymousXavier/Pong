#include "MovementSystem.h"
#include "../../configs/settings.h"

void MovementSystem::process_moveEvents(
    EntityManager &entityManager, EventsManager &eventsManager
) {
  // Pass by const reference (&) to avoid copying the event in memory 60 times a second
  for (const GameEvent &gameEvent : eventsManager.getEvent()) {
    if (gameEvent.type == EventType::MoveIntent) {
      if (entityManager.spatialComponents.count(gameEvent.movement.id)) {
        SpatialComponent &spatialComp =
            entityManager.spatialComponents[gameEvent.movement.id];

        // 1. Cast to a signed integer to safely calculate negative movement
        int newX =
            spatialComp.x + (gameEvent.movement.dx * gameEvent.movement.moveSpeed);
        int newY =
            spatialComp.y + (gameEvent.movement.dy * gameEvent.movement.moveSpeed);

        // 2. The boundary check now safely evaluates negative numbers
        // Dont Auto Keep withing screen if its the ball
        if (!entityManager.ballTags.count(gameEvent.movement.id)) {
          if (newY < 0) {
            spatialComp.y = 0;
          } else if ((newY + spatialComp.h) > screen_height) {
            spatialComp.y = screen_height - spatialComp.h;
          } else {
            // 3. Cast back to unsigned only when we know it is safely within bounds
            spatialComp.y = newY;
          }

          if (newX < 0) {
            spatialComp.x = 0;
          } else if ((newX + spatialComp.w) > screen_width) {
            spatialComp.x = screen_width - spatialComp.w;
          } else {
            // 3. Cast back to unsigned only when we know it is safely within bounds
            spatialComp.x = newX;
          }
        } else {
          spatialComp.y = newY;
          spatialComp.x = newX;
        }
      }
    }
  }
}