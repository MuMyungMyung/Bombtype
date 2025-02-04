#pragma once
#include "IEventSystem.hpp"
#include "IRenderSystem.hpp"
#include "IUpdateSystem.hpp"
#include <type_traits>

namespace ecs {

class SystemManager {
public:
  template <typename T, typename... Args> void addUpdateSystem(Args &&...args) {
    static_assert(std::is_base_of<IUpdateSystem, T>::value, "T must inherit from IUpdateSystem");
    m_updateSystems.push_back(std::make_unique<T>(std::forward<Args>(args)...));
  }
  template <typename T, typename... Args> void addEventSystem(Args &&...args) {
    static_assert(std::is_base_of<IEventSystem, T>::value, "T must inherit from IEventSystem");
    m_eventSystems.push_back(std::make_unique<T>(std::forward<Args>(args)...));
  }

  template <typename T, typename... Args> void addRenderSystem(Args &&...args) {
    static_assert(std::is_base_of<IRenderSystem, T>::value, "T must inherit from IRenderSystem");
    m_renderSystems.push_back(std::make_unique<T>(std::forward<Args>(args)...));
  }

  void update(EntityManager &entityManager, float deltaTime) {
    for (auto &system : m_updateSystems) {
      system->update(entityManager, deltaTime);
    }
  }

  void render(EntityManager &entityManager, sf::RenderWindow &window) {
    for (auto &system : m_renderSystems) {
      system->render(entityManager, window);
    }
  }

  void handleEvents(EntityManager &entityManager, const sf::Event &event) {
    for (auto &system : m_eventSystems) {
      system->handleEvent(entityManager, event);
    }
  }

private:
  std::vector<std::unique_ptr<IUpdateSystem>> m_updateSystems;
  std::vector<std::unique_ptr<IEventSystem>> m_eventSystems;
  std::vector<std::unique_ptr<IRenderSystem>> m_renderSystems;
};

} // namespace ecs
