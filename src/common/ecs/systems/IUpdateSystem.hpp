#pragma once

#include "ecs/entities/EntityManager.hpp"

namespace ecs {
namespace systems {

class IUpdateSystem {
public:
  virtual ~IUpdateSystem() = default;
  virtual void update(EntityManager &, float) = 0;
};

} // namespace systems
} // namespace ecs
