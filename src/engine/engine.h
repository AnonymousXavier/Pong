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
void draw_number(int value, int x, int y, WORD color);
