#pragma once

#include "Component.hpp"
#include <SFML/System/Vector2.hpp>

namespace ecs {

class TransformComponent : public Component {
public:
  sf::Vector2i position;

  TransformComponent(sf::Vector2i position = {0, 0}) : position(position) {}
};

} // namespace ecs
