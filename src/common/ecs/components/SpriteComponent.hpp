#pragma once

#include "Component.hpp"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <nlohmann/json.hpp>
#include <stdexcept>
#include <string>

namespace ecs {
class SpriteComponent : public Component {
public:
  sf::Sprite sprite;
  sf::Texture texture;
  std::string texturePath;
  SpriteComponent(const std::string &texturePath) : texturePath(texturePath) {
    if (!texture.loadFromFile(texturePath)) {
      throw std::runtime_error("Failed to load texture: " + texturePath);
    }
    sprite.setTexture(texture);
  }

  SpriteComponent(const nlohmann::json &j) : SpriteComponent(j.at("texturePath").get<std::string>()) {
  }

  friend void to_json(nlohmann::json &j, const SpriteComponent &s) {
    j = nlohmann::json({"texturePath", s.texturePath});
  }
};
} // namespace ecs
