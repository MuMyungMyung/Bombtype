#include "MyWorld.hpp"
#include "ecs/components/AnimationComponent.hpp"
#include "ecs/components/ComponentFactory.hpp"
#include "ecs/components/HealthComponent.hpp"
#include "ecs/components/InputComponent.hpp"
#include "ecs/components/MapComponent.hpp"
#include "ecs/components/MovementComponent.hpp"
#include "ecs/components/NetworkComponent.hpp"
#include "ecs/components/PlayerComponent.hpp"
#include "ecs/systems/BombSystem.hpp"
#include "ecs/systems/ExplosionRenderSystem.hpp"
#include "ecs/systems/ExplosionSystem.hpp"
#include "ecs/systems/InputSystem.hpp"
#include "ecs/systems/MapRenderSystem.hpp"
#include "ecs/systems/MovementSystem.hpp"
#include "ecs/systems/NetworkSystem.hpp"
#include "ecs/systems/RenderSystem.hpp"
#include <fstream>

void MyWorld::init() {
  m_systemManager.addEventSystem<ecs::systems::InputSystem>();
  m_systemManager.addUpdateSystem<ecs::systems::MovementSystem>();
  m_systemManager.addUpdateSystem<ecs::systems::NetworkSystem>();
  m_systemManager.addUpdateSystem<ecs::systems::ExplosionSystem>();
  m_systemManager.addUpdateSystem<ecs::systems::BombSystem>();
  m_systemManager.addRenderSystem<ecs::systems::MapRenderSystem>();
  m_systemManager.addRenderSystem<ecs::systems::ExplosionRenderSystem>();
  m_systemManager.addRenderSystem<ecs::systems::RenderSystem>();

  auto &compFactory = ecs::ComponentFactory::getInstance();

  compFactory.registerComponent<ecs::AnimationComponent>("AnimationComponent");
  compFactory.registerComponent<ecs::BombComponent>("BombComponent");
  compFactory.registerComponent<ecs::ExplosionComponent>("ExplosionComponent");
  compFactory.registerComponent<ecs::HealthComponent>("HealthComponent");
  compFactory.registerComponent<ecs::InputComponent>("InputComponent");
  compFactory.registerComponent<ecs::MapComponent>("MapComponent");
  compFactory.registerComponent<ecs::MovementComponent>("MovementComponent");
  compFactory.registerComponent<ecs::NetworkComponent>("NetworkComponent");
  compFactory.registerComponent<ecs::PlayerComponent>("PlayerComponent");
  compFactory.registerComponent<ecs::SpriteComponent>("SpriteComponent");
  compFactory.registerComponent<ecs::TransformComponent>("TransformComponent");
}

void MyWorld::loadGame(const std::string &filepath) {

  std::ifstream file(filepath);

  if (!file.is_open()) {
    throw std::runtime_error("Failed to open json file " + filepath);
  }
  nlohmann::json entitiesJson;

  file >> entitiesJson;
  file.close();

  auto &factory = ecs::ComponentFactory::getInstance();

  for (const auto &entityJson : entitiesJson) {
    auto entity = m_entityManager.createEntity();

    for (auto &[compName, compData] : entityJson["components"].items()) {
#ifdef DEBUG
      std::cout << "Creating component " << compName << std::endl;
#endif
      auto component = factory.createComponent(compName, compData);
      entity->grabComponent(component);
    }
  }
}
