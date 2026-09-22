#include "EntityManager.h"
#include "ECS/components.h"

EntityID EntityManager::CreateEntity() { return nextEntityId++; }
void EntityManager::setPlayerID(EntityID id) { playerID = id; }
EntityID EntityManager::getPlayerID() { return playerID; }

void EntityManager::DeleteEntity(EntityID id) {
  if (EntityManager::HasBallTag(id)) {
    ballTags.erase(id);
  }
  if (EntityManager::HasEnemyTag(id)) {
    enemyTags.erase(id);
  }
  if (EntityManager::HasRenderComponent(id)) {
    renderComponents.erase(id);
  }
  if (EntityManager::HasSpatialComponent(id)) {
    spatialComponents.erase(id);
  }
  if (EntityManager::HasVelocityComponent(id)) {
    velocityComponents.erase(id);
  }
}

// Add Functions
void EntityManager::AddComponent(EntityID id, SpatialComponent component) {
  spatialComponents[id] = component;
}
void EntityManager::AddComponent(EntityID id, RenderComponent component) {
  renderComponents[id] = component;
}
void EntityManager::AddComponent(EntityID id, EnemyTag component) {
  enemyTags[id] = component;
}
void EntityManager::AddComponent(EntityID id, BallTag component) {
  ballTags[id] = component;
}
void EntityManager::AddComponent(EntityID id, VelocityComponent component) {
  velocityComponents[id] = component;
}

// Has Functions
bool EntityManager::HasSpatialComponent(EntityID id) {
  return spatialComponents.count(id);
}
bool EntityManager::HasRenderComponent(EntityID id) {
  return renderComponents.count(id);
}
bool EntityManager::HasEnemyTag(EntityID id) { return enemyTags.count(id); }
bool EntityManager::HasBallTag(EntityID id) { return ballTags.count(id); }
bool EntityManager::HasVelocityComponent(EntityID id) {
  return velocityComponents.count(id);
}
