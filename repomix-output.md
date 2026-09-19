This file is a merged representation of the entire codebase, combined into a single document by Repomix.

# File Summary

## Purpose
This file contains a packed representation of the entire repository's contents.
It is designed to be easily consumable by AI systems for analysis, code review,
or other automated processes.

## File Format
The content is organized as follows:
1. This summary section
2. Repository information
3. Directory structure
4. Repository files (if enabled)
5. Multiple file entries, each consisting of:
  a. A header with the file path (## File: path/to/file)
  b. The full contents of the file in a code block

## Usage Guidelines
- This file should be treated as read-only. Any changes should be made to the
  original repository files, not this packed version.
- When processing this file, use the file path to distinguish
  between different files in the repository.
- Be aware that this file may contain sensitive information. Handle it with
  the same level of security as you would the original repository.

## Notes
- Some files may have been excluded based on .gitignore rules and Repomix's configuration
- Binary files are not included in this packed representation. Please refer to the Repository Structure section for a complete list of file paths, including binary files
- Files matching patterns in .gitignore are excluded
- Files matching default ignore patterns are excluded
- Files are sorted by Git change count (files with more changes are at the bottom)

# Directory Structure
```
src/
  configs/
    settings.h
  ECS/
    Managers/
      EntityManager.cpp
      EntityManager.h
      EventsManager.cpp
      EventsManager.h
    Systems/
      BallController.cpp
      BallController.h
      InputSystem.cpp
      InputSystem.h
      MovementSystem.cpp
      MovementSystem.h
      PlayerController.cpp
      PlayerController.h
      RenderingSystem.cpp
      RenderingSystem.h
    components.h
  engine/
    engine.cpp
    engine.h
  Factories.cpp
  Factories.h
.clang-format
.clangd
CMakeLists.txt
main.cpp
```

# Files

## File: src/configs/settings.h
```c
#pragma once

#include <windows.h>

constexpr short screen_width = 100;
constexpr short screen_height = screen_width / 4;

constexpr short padheight = 5;
constexpr short padWidth = 1;
constexpr int padMoveSpeed = 1;

namespace Colors {
constexpr WORD BLACK = 0x0000;
constexpr WORD WHITE = BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_BLUE;
constexpr WORD WHITE_TEXT = FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN;
} // namespace Colors
```

## File: src/ECS/Managers/EntityManager.cpp
```cpp
#include "EntityManager.h"

EntityID EntityManager::CreateEntity() { return nextEntityId++; }
void EntityManager::setPlayerID(EntityID id) { playerID = id; }
EntityID EntityManager::getPlayerID() { return playerID; }

// Add Functions
void EntityManager::AddComponent(EntityID id, SpatialComponent component) {
  spatialComponents[id] = component;
}
void EntityManager::AddComponent(EntityID id, RenderComponent component) {
  renderComponents[id] = component;
}
void EntityManager::AddComponent(EntityID id, EnemyTag component) {
  enemyTags[id] = component;
}
void EntityManager::AddComponent(EntityID id, BallTag component) {
  ballTags[id] = component;
}
void EntityManager::AddComponent(EntityID id, VelocityComponent component) {
  velocityComponents[id] = component;
}
```

## File: src/ECS/Managers/EntityManager.h
```c
#pragma once

#include "../components.h"
#include <unordered_map>

using EntityID = unsigned int;

class EntityManager {
private:
  EntityID nextEntityId = 0;
  EntityID playerID;

public:
  // Dictionary for each component type
  std::unordered_map<int, SpatialComponent> spatialComponents = {};
  std::unordered_map<int, RenderComponent> renderComponents = {};
  std::unordered_map<int, VelocityComponent> velocityComponents = {};
  std::unordered_map<int, EnemyTag> enemyTags = {};
  std::unordered_map<int, BallTag> ballTags = {};

  EntityID CreateEntity();
  void setPlayerID(EntityID id);
  EntityID getPlayerID();

  void AddComponent(EntityID id, SpatialComponent component);
  void AddComponent(EntityID id, RenderComponent component);
  void AddComponent(EntityID id, EnemyTag component);
  void AddComponent(EntityID id, BallTag component);
  void AddComponent(EntityID id, VelocityComponent component);
};
```

## File: src/ECS/Managers/EventsManager.cpp
```cpp
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
```

## File: src/ECS/Managers/EventsManager.h
```c
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
```

## File: src/ECS/Systems/BallController.cpp
```cpp
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
```

## File: src/ECS/Systems/BallController.h
```c
#pragma once

#include "ECS/Managers/EntityManager.h"
#include "ECS/Managers/EventsManager.h"
#include <windef.h>

class BallController {
public:
  static void process(EventsManager &eventsManager, EntityManager &entityManager);
};
```

## File: src/ECS/Systems/InputSystem.cpp
```cpp
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
```

## File: src/ECS/Systems/InputSystem.h
```c
#pragma once

#include "../Managers/EventsManager.h"
#include <windows.h>

class InputSystem {
public:
  static void process_events(EventsManager &eventManager);
};
```

## File: src/ECS/Systems/MovementSystem.cpp
```cpp
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
```

## File: src/ECS/Systems/MovementSystem.h
```c
#include "ECS/Managers/EntityManager.h"
#include "ECS/Managers/EventsManager.h"

class MovementSystem {
public:
  static void
  process_moveEvents(EntityManager &entityManager, EventsManager &eventsManager);
};
```

## File: src/ECS/Systems/PlayerController.cpp
```cpp
#include "PlayerController.h"
#include "../../configs/settings.h"
#include <windows.h>

void PlayerController::process(
    EntityManager &entityManager, EventsManager &eventsManager
) {

  for (const GameEvent &gameEvent : eventsManager.getEvent()) {
    switch (gameEvent.type) {
    case EventType::MoveIntent:
      break;
    case EventType::keyPress:
      PlayerController::process_movement(
          eventsManager, entityManager.getPlayerID(), gameEvent.key.keyCode
      );
      break;
    }
  }
}

void PlayerController::process_movement(
    EventsManager &eventsManager, EntityID playerID, WORD pressedKey
) {
  if (pressedKey != VK_UP && pressedKey != VK_DOWN) {
    return;
  }

  MoveEvent moveEvent;
  moveEvent.id = playerID;
  moveEvent.moveSpeed = padMoveSpeed;

  if (pressedKey == VK_DOWN) {
    moveEvent.dx = 0;
    moveEvent.dy = 1;
  } else if (pressedKey == VK_UP) {
    moveEvent.dx = 0;
    moveEvent.dy = -1;
  }

  eventsManager.AddEvent(moveEvent);
}
```

## File: src/ECS/Systems/PlayerController.h
```c
#pragma once
#include "ECS/Managers/EventsManager.h"
#include <windows.h>

class PlayerController {
public:
  static void
  process_movement(EventsManager &eventsManager, EntityID playerID, WORD pressedKey);
  static void process(EntityManager &entityManager, EventsManager &eventsManager);
};
```

## File: src/ECS/Systems/RenderingSystem.cpp
```cpp
#include "RenderingSystem.h"

void RenderingSystem::process(EntityManager &manager) {
  for (auto &[entityId, renderComponent] : manager.renderComponents) {
    if (manager.spatialComponents.count(entityId)) {
      RenderComponent renderComp = manager.renderComponents[entityId];
      SpatialComponent spatialComp = manager.spatialComponents[entityId];

      draw_rect(
          spatialComp.x,
          spatialComp.y,
          spatialComp.w,
          spatialComp.h,
          renderComp.color,
          renderComp.letter
      );
    }
  }
}
```

## File: src/ECS/Systems/RenderingSystem.h
```c
#pragma once

#include "ECS/Managers/EntityManager.h"
#include "engine/engine.h"

class RenderingSystem {
public:
  static void process(EntityManager& manager);
};
```

## File: src/ECS/components.h
```c
#pragma once

#include <windows.h>

struct SpatialComponent {
  unsigned int x;
  unsigned int y;
  unsigned int w;
  unsigned int h;
};

struct RenderComponent {
  WORD color;
  char letter = ' ';
};

struct VelocityComponent {
  unsigned int moveSpeed;
  int dx;
  int dy;
};

struct PlayerTag {};
struct BallTag {};
struct EnemyTag {};
```

## File: src/engine/engine.cpp
```cpp
#include "engine.h"
#include <cstdlib>
#include <minwindef.h>
#include "configs/settings.h"

HANDLE rHnd; // The Read Console Handle
HANDLE wHnd; // The Write Console Handle

CHAR_INFO screenBuffer[screen_width * screen_height];

HANDLE get_read_handle() { // Returns the read handle of the console
  return rHnd;
}

void setup_console() {
  AllocConsole();

  rHnd = GetStdHandle(STD_INPUT_HANDLE);
  wHnd = GetStdHandle(STD_OUTPUT_HANDLE);

  SMALL_RECT windowSize = {0, 0, screen_width, screen_height};
  COORD bufferSize = {screen_width + 1, screen_height + 1};

  // Set it to a small size first to ensire the buffer updates accordingly
  SMALL_RECT tempSize = {0, 0, 1, 1};
  SetConsoleWindowInfo(wHnd, TRUE, &tempSize);
  SetConsoleScreenBufferSize(wHnd, bufferSize);

  // Unfortunately there always be 1 more cell on the right and bottom of the screen
  SetConsoleWindowInfo(wHnd, TRUE, &windowSize);
}

void draw_rect(
    unsigned short x,
    unsigned short y,
    unsigned short w,
    unsigned short h,
    WORD color,
    WORD icon
) {
  w = w; // so a 1x1 cell looks like a box not a rect
  bool inRange = x >= 0 && y >= 0 && x <= screen_width && y <= screen_height;

  if (inRange) {
    for (int iy = 0; iy < h; iy++) {
      for (int ix = 0; ix < w; ix++) {
        int _x = x + ix;
        int _y = y + iy;

        if (_x >= screen_width || _y >= screen_height) {
          continue;
        }
        int i = _y * screen_width + _x;

        CHAR_INFO &letter = screenBuffer[i];
        letter.Char.AsciiChar = icon;
        letter.Attributes = color;
      }
    }
  }
}

void render_frame() {
  COORD bufferSize = {screen_width, screen_height};
  COORD topLeft = {0, 0};
  SMALL_RECT writeArea = {
      topLeft.X, topLeft.Y, (short)(bufferSize.X - 1), (short)(bufferSize.Y - 1)
  };

  WriteConsoleOutput(wHnd, screenBuffer, bufferSize, topLeft, &writeArea);
}

void clear_console() {
  for (int i = 0; i < screen_width * screen_height; i++) {
    screenBuffer[i].Char.AsciiChar = ' ';
    screenBuffer[i].Attributes = Colors::BLACK;
  }
}
```

## File: src/engine/engine.h
```c
#pragma once

#include <minwindef.h>
#include <wincontypes.h>
#include <winnt.h>

/// Get the Read Handle of the Console
HANDLE get_read_handle();

void setup_console();
void draw_rect(
    unsigned short x,
    unsigned short y,
    unsigned short w,
    unsigned short h,
    WORD color,
    WORD icon
);
void render_frame();
void clear_console();
```

## File: src/Factories.cpp
```cpp
#include "Factories.h"
#include "ECS/Managers/EntityManager.h"

EntityID create_pad(
    EntityManager &manager,
    unsigned int x,
    unsigned int y,
    unsigned int w,
    unsigned int h,
    WORD color
) {
  EntityID padId = manager.CreateEntity();

  manager.AddComponent(padId, RenderComponent{color});
  manager.AddComponent(padId, SpatialComponent{x, y, w, h});

  return padId;
};

EntityID create_ball(
    EntityManager &manager,
    unsigned int x,
    unsigned int y,
    WORD color,
    POINT moveDirection
) {
  EntityID ballID = manager.CreateEntity();

  manager.AddComponent(ballID, RenderComponent{color, 'O'});
  manager.AddComponent(ballID, SpatialComponent({x, y, 1, 1}));
  manager.AddComponent(ballID, VelocityComponent{1, moveDirection.x, moveDirection.y});
  manager.AddComponent(ballID, BallTag{});

  return ballID;
}
```

## File: src/Factories.h
```c
#pragma once

#include "ECS/Managers/EntityManager.h"

EntityID create_pad(
    EntityManager &manager,
    unsigned int x,
    unsigned int y,
    unsigned int w,
    unsigned int h,
    WORD color
);
EntityID create_ball(
    EntityManager &manager,
    unsigned int x,
    unsigned int y,
    WORD color,
    POINT moveDirection
);
```

## File: .clang-format
```
BasedOnStyle: LLVM
ColumnLimit: 88
IndentWidth: 2
AlignAfterOpenBracket: BlockIndent
BinPackArguments: false
BinPackParameters: false
BreakBeforeBraces: Attach
```

## File: .clangd
```
CompileFlags:
    Add: [-std=c++20]
    CompilationDatabase: build/

Completion:
    AllScopes: No

Index:
    StandardLibrary: No
```

## File: CMakeLists.txt
```
# 1. Enforce a minimum version of CMake so features don't break
cmake_minimum_required(VERSION 3.10)

# 2. Name your project and state that we are writing C++
project(TestProject VERSION 1.0 LANGUAGES CXX)

# 3. Generate a compilation database (this is what gives Kate/clangd its autocompletion smarts)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# 4. Lock in modern C++ features (C++20)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1. Find all .cpp files inside the src/ directory and its subdirectories.
# The CONFIGURE_DEPENDS flag forces CMake to notice when you create a new file.
file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS "src/*.cpp")

# 2. Tell the compiler to compile main.cpp and everything it found in src/
add_executable(App main.cpp ${SRC_FILES})

# 3. Tell CMake that any #include can start looking from the "src" folder
target_include_directories(App PRIVATE src)
```

## File: main.cpp
```cpp
#include "ECS/Managers/EntityManager.h"
#include "ECS/Managers/EventsManager.h"
#include "ECS/Systems/BallController.h"
#include "ECS/Systems/InputSystem.h"
#include "ECS/Systems/MovementSystem.h"
#include "ECS/Systems/PlayerController.h"
#include "ECS/Systems/RenderingSystem.h"
#include "Factories.h"
#include "configs/settings.h"
#include "engine/engine.h"
#include <synchapi.h>

bool appRunning = true;

EntityManager entityManager;
EventsManager eventsManager;

void draw() {
  clear_console();
  RenderingSystem::process(entityManager);
  render_frame();
}

void update() {
  eventsManager.process();
  InputSystem::process_events(eventsManager);

  PlayerController::process(entityManager, eventsManager);
  BallController::process(eventsManager, entityManager);

  MovementSystem::process_moveEvents(entityManager, eventsManager);
}

void setup() {
  EntityID playerID = create_pad(
      entityManager,
      2,
      (screen_height - padheight) / 2,
      padWidth,
      padheight,
      Colors::WHITE
  );

  entityManager.setPlayerID(playerID);
  create_ball(
      entityManager, screen_width / 2, screen_height / 2, Colors::WHITE_TEXT, {1, 1}
  );

  create_pad(
      entityManager,
      screen_width - padWidth - 2,
      (screen_height - padheight) / 2,
      padWidth,
      padheight,
      Colors::WHITE
  );
  setup_console();
}

int main() {
  setup();
  while (appRunning) {
    draw();
    update();
    Sleep(60);
  }
}
```
