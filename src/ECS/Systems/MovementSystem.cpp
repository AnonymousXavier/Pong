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
        int newX = static_cast<int>(spatialComp.x) +
                   (gameEvent.movement.dx * gameEvent.movement.moveSpeed);
        int newY = static_cast<int>(spatialComp.y) +
                   (gameEvent.movement.dy * gameEvent.movement.moveSpeed);

        // 2. The boundary check now safely evaluates negative numbers
        if (newY < 0) {
          spatialComp.y = 0;
        } else if ((newY + static_cast<int>(spatialComp.h)) > screen_height) {
          spatialComp.y = screen_height - spatialComp.h;
        } else {
          // 3. Cast back to unsigned only when we know it is safely within bounds
          spatialComp.y = static_cast<unsigned int>(newY);
        }
        
        if (newX < 0) {
          spatialComp.x = 0;
        } else if ((newX + static_cast<int>(spatialComp.w)) > screen_width) {
          spatialComp.x = screen_width - spatialComp.w;
        } else {
          // 3. Cast back to unsigned only when we know it is safely within bounds
          spatialComp.x = static_cast<unsigned int>(newX);
        }
      }
    }
  }
}