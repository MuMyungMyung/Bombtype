#include "World.hpp"

namespace ecs {

void World::updateSystems(float deltaTime) {
  m_systemManager.update(m_entityManager, deltaTime);
}

void World::handleEvents(const sf::Event &event) {
  m_systemManager.handleEvents(m_entityManager, event);
}

void World::render(sf::RenderWindow &window) {
  window.clear();
  m_systemManager.render(m_entityManager, window);
  window.display();
}

} // namespace ecs
