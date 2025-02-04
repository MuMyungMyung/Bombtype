#pragma once

#include "Component.hpp"

namespace ecs {
class CollisionComponent : public Component {
public:
  bool isSolid;

  CollisionComponent(bool solid = true) : isSolid(solid) {
  }
};
} // namespace ecs
