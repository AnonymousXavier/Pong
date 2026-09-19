#pragma once

#include "../components.h"
#include <unordered_map>

using EntityID = unsigned int;

class EntityManager {
private:
  EntityID nextEntityId = 0;
  EntityID playerID;

public:
  // Dictionary for each component type
  std::unordered_map<int, SpatialComponent> spatialComponents = {};
  std::unordered_map<int, RenderComponent> renderComponents = {};
  std::unordered_map<int, VelocityComponent> velocityComponents = {};
  std::unordered_map<int, EnemyTag> enemyTags = {};
  std::unordered_map<int, BallTag> ballTags = {};

  EntityID CreateEntity();
  void setPlayerID(EntityID id);
  EntityID getPlayerID();

  void AddComponent(EntityID id, SpatialComponent component);
  void AddComponent(EntityID id, RenderComponent component);
  void AddComponent(EntityID id, EnemyTag component);
  void AddComponent(EntityID id, BallTag component);
  void AddComponent(EntityID id, VelocityComponent component);
};