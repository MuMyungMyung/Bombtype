#pragma once

#include "ecs/World.hpp"

class MyWorld : public ecs::World {
public:
  void init();

  void loadGame(const std::string &filepath);
};
