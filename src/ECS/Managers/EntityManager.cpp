#include "EntityManager.h"

EntityID EntityManager::CreateEntity() { return nextEntityId++; }
void EntityManager::setPlayerID(EntityID id) { playerID = id; }
EntityID EntityManager::getPlayerID() { return playerID; }

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
