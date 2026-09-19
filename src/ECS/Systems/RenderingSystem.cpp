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
