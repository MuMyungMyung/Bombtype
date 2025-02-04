#include "ecs/World.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <chrono>

#include <SFML/Graphics.hpp>
#include <thread>

int main(int argc, char *argv[]) {

  sf::RenderWindow renderWindow(sf::VideoMode(800, 600), "BomberType");
  ecs::World world;

  // 16ms for ~60 updates per second
  constexpr std::chrono::milliseconds updateIntervals(16);
  auto previousTime = std::chrono::high_resolution_clock::now();

  while (renderWindow.isOpen()) {
    sf::Event event;
    while (renderWindow.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        renderWindow.close();
      world.handleEvents(event);
    }
    auto currentTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> deltaTime = currentTime - previousTime;
    previousTime = currentTime;

    world.updateSystems(deltaTime.count());
    world.render(renderWindow);

    auto elapsedTime = std::chrono::high_resolution_clock::now() - currentTime;
    auto sleepTime = updateIntervals - std::chrono::duration_cast<std::chrono::milliseconds>(elapsedTime);

    // Sleep the amount of time remaining before next update
    if (sleepTime > std::chrono::milliseconds::zero())
      std::this_thread::sleep_for(sleepTime);
  }
  return 0;
}
