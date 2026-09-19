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