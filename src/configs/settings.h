#pragma once

#include <windows.h>

constexpr short screen_width = 100;
constexpr short screen_height = screen_width / 4;

constexpr short padheight = 7;
constexpr short padWidth = 1;
constexpr int padMoveSpeed = 1;

namespace Colors {
constexpr WORD BLACK = 0x0000;
constexpr WORD WHITE = BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_BLUE;
constexpr WORD WHITE_TEXT = FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN;
} // namespace Colors
