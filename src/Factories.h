#pragma once

#include "ECS/Managers/EntityManager.h"

EntityID create_pad(EntityManager &manager, int x, int y, int w, int h, WORD color);
EntityID
create_ball(EntityManager &manager, int x, int y, WORD color, POINT moveDirection);