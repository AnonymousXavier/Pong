#include "Factories.h"
#include "ECS/Managers/EntityManager.h"

EntityID create_pad(EntityManager &manager, int x, int y, int w, int h, WORD color) {
  EntityID padId = manager.CreateEntity();

  manager.AddComponent(padId, RenderComponent{color});
  manager.AddComponent(padId, SpatialComponent{x, y, w, h});

  return padId;
};

EntityID
create_ball(EntityManager &manager, int x, int y, WORD color, POINT moveDirection) {
  EntityID ballID = manager.CreateEntity();

  manager.AddComponent(ballID, RenderComponent{color, 'O'});
  manager.AddComponent(ballID, SpatialComponent({x, y, 1, 1}));
  manager.AddComponent(ballID, VelocityComponent{1, moveDirection.x, moveDirection.y});
  manager.AddComponent(ballID, BallTag{});

  return ballID;
}