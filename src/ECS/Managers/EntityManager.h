#pragma once

#include "../components.h"
#include <unordered_map>

using EntityID = unsigned int;

class EntityManager {
public:
  EntityID INVALID_ENTITY = 0;

  // Dictionary for each component type
  std::unordered_map<int, SpatialComponent> spatialComponents = {};
  std::unordered_map<int, RenderComponent> renderComponents = {};
  std::unordered_map<int, VelocityComponent> velocityComponents = {};
  std::unordered_map<int, EnemyTag> enemyTags = {};
  std::unordered_map<int, BallTag> ballTags = {};

  EntityID CreateEntity();
  void DeleteEntity(EntityID id);
  void setPlayerID(EntityID id);
  EntityID getPlayerID();

  void AddComponent(EntityID id, SpatialComponent component);
  void AddComponent(EntityID id, RenderComponent component);
  void AddComponent(EntityID id, EnemyTag component);
  void AddComponent(EntityID id, BallTag component);
  void AddComponent(EntityID id, VelocityComponent component);

  bool HasSpatialComponent(EntityID id);
  bool HasRenderComponent(EntityID id);
  bool HasEnemyTag(EntityID id);
  bool HasBallTag(EntityID id);
  bool HasVelocityComponent(EntityID id);

private:
  EntityID playerID;
  EntityID nextEntityId = INVALID_ENTITY + 1;
};