#include "InputSystem.h"
#include "../../engine/engine.h"

void InputSystem::process_events(EventsManager &eventManager) {
  DWORD numEvents = 0;

  GetNumberOfConsoleInputEvents(get_read_handle(), &numEvents);
  if (numEvents != 0) {
    INPUT_RECORD eventsBuffer[128];

    // Keep the number of events readable less than eventBufferSize
    DWORD eventsToRead = numEvents <= 128 ? numEvents : 128;
    DWORD actualEventsRead = 0;
    ReadConsoleInput(get_read_handle(), eventsBuffer, eventsToRead, &actualEventsRead);

    for (int i = 0; i < 128; i++) {
      INPUT_RECORD event = eventsBuffer[i];
      if (event.EventType == KEY_EVENT && event.Event.KeyEvent.bKeyDown) {
        KeyDownEvent keyEvent;
        keyEvent.keyCode = event.Event.KeyEvent.wVirtualKeyCode;

        eventManager.AddEvent(keyEvent);
      }
    }
  }
}
