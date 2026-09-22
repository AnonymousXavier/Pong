#pragma once

#include "ECS/Managers/EntityManager.h"
#include <vector>

enum class EventType { MoveIntent, keyPress, collisionEvent };

// Define Specific Event Types
struct KeyDownEvent {
  WORD keyCode;
};

struct MoveEvent {
  EntityID id;
  int dx;
  int dy;
  unsigned int moveSpeed;
};

struct CollisionEvent {
  EntityID ballID;
  EntityID padID;
};

// Define the Generic Event Type
struct GameEvent {
  EventType type;

  union {
    MoveEvent movement;
    KeyDownEvent key;
    CollisionEvent collision;
  };
};

class EventsManager {
private:
  std::vector<GameEvent> events;

public:
  const std::vector<GameEvent>& getEvent() const;
  void clearEvent();
  void AddEvent(MoveEvent moveEvent);
  void AddEvent(KeyDownEvent keyPress);
  void AddEvent(CollisionEvent collision);
  void process();
};