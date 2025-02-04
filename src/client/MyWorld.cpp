#include "MyWorld.hpp"
#include "ecs/systems/InputSystem.hpp"
#include "ecs/systems/MovementSystem.hpp"
#include "ecs/systems/NetworkSystem.hpp"

void MyWorld::init() {
  m_systemManager.addEventSystem<ecs::systems::InputSystem>();
  m_systemManager.addUpdateSystem<ecs::systems::MovementSystem>();
  m_systemManager.addUpdateSystem<ecs::systems::NetworkSystem>();
}
