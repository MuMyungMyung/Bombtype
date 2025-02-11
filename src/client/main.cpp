#include "MyWorld.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <chrono>

#include <SFML/Graphics.hpp>
#include <iostream>
#include <thread>

int main(int argc, char *argv[]) {

  sf::RenderWindow window(sf::VideoMode(sf::Vector2u(800, 600)), "BomberType");
  MyWorld world;

  // 16ms for ~60 updates per second
  constexpr std::chrono::milliseconds updateIntervals(16);
  auto previousTime = std::chrono::high_resolution_clock::now();

  window.setFramerateLimit(60);
  world.init();
  try {
    world.loadGame("assets/entities.json");
  } catch (const std::exception &e) {
    std::cerr << e.what() << std::endl;
    window.close();
    return -1;
  }
  while (window.isOpen()) {
    while (std::optional event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>())
        window.close();
      world.handleEvents(event);
    }
    auto currentTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> deltaTime = currentTime - previousTime;
    previousTime = currentTime;

    world.updateSystems(deltaTime.count());
    world.render(window);

    auto elapsedTime = std::chrono::high_resolution_clock::now() - currentTime;
    auto sleepTime = updateIntervals - std::chrono::duration_cast<std::chrono::milliseconds>(elapsedTime);

    // Sleep the amount of time remaining before next update
    if (sleepTime > std::chrono::milliseconds::zero())
      std::this_thread::sleep_for(sleepTime);
  }
  return 0;
}
