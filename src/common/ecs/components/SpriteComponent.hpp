#pragma once

#include "Component.hpp"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <stdexcept>
#include <string>

namespace ecs {
class SpriteComponent : public Component {
public:
  sf::Sprite sprite;
  sf::Texture texture;
  SpriteComponent(const std::string &texturePath) {
    if (!texture.loadFromFile(texturePath)) {
      throw std::runtime_error("Failed to load texture: " + texturePath);
    }
    sprite.setTexture(texture);
  }
};
} // namespace ecs
