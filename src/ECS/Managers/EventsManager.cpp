#include "EventsManager.h"
#include <vector>

std::vector<EventType> events;

std::vector<GameEvent> EventsManager::getEvent() { return events; }

void EventsManager::AddEvent(MoveEvent moveEvent) {
  GameEvent gameEvent;
  gameEvent.type = EventType::MoveIntent;
  gameEvent.movement = moveEvent;

  events.push_back(gameEvent);
};

void EventsManager::AddEvent(KeyDownEvent keyPressEvent) {
  GameEvent gameEvent;
  gameEvent.type = EventType::keyPress;
  gameEvent.key = keyPressEvent;

  events.push_back(gameEvent);
};

void EventsManager::clearEvent() { events.clear(); }

void EventsManager::process() { EventsManager::clearEvent(); }