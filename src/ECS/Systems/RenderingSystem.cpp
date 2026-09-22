#include "RenderingSystem.h"

void RenderingSystem::process(EntityManager &manager) {
  for (auto &[entityId, renderComp] : manager.renderComponents) {
    if (manager.spatialComponents.count(entityId)) {
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
