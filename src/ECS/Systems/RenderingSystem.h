#pragma once

#include "ECS/Managers/EntityManager.h"
#include "engine/engine.h"

class RenderingSystem {
public:
  static void process(EntityManager& manager);
};