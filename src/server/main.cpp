#include "ecs/World.hpp"
#include <chrono>
#include <csignal>
#include <thread>

static std::atomic<bool> run = true;

static void handler(int) {
  run = false;
}

int main(int argc, char *argv[]) {
  ecs::World world;

  // 16ms for ~60 updates per second
  constexpr std::chrono::milliseconds updateIntervals(16);
  auto previousTime = std::chrono::high_resolution_clock::now();
  std::signal(SIGINT, handler);

  while (run) {
    auto currentTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> deltaTime = currentTime - previousTime;
    previousTime = currentTime;

    world.updateSystems(deltaTime.count());

    auto elapsedTime = std::chrono::high_resolution_clock::now() - currentTime;
    auto sleepTime = updateIntervals - std::chrono::duration_cast<std::chrono::milliseconds>(elapsedTime);

    // Sleep the amount of time remaining before next update
    if (sleepTime > std::chrono::milliseconds::zero())
      std::this_thread::sleep_for(sleepTime);
  }
  return 0;
}
