#pragma once

#include "ECS/Managers/EntityManager.h"
#include <vector>

enum class EventType { MoveIntent, keyPress };

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

// Define the Generic Event Type
struct GameEvent {
  EventType type;

  union {
    MoveEvent movement;
    KeyDownEvent key;
  };
};

class EventsManager {
private:
  std::vector<GameEvent> events;

public:
  std::vector<GameEvent> getEvent();
  void clearEvent();
  void AddEvent(MoveEvent moveEvent);
  void AddEvent(KeyDownEvent keyPress);
  void process();
};