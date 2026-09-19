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