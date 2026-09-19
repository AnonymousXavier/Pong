#pragma once

#include "../Managers/EventsManager.h"
#include <windows.h>

class InputSystem {
public:
  static void process_events(EventsManager &eventManager);
};