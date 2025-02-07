#pragma once

#include "Component.hpp"
#include "ecs/serialization/IntRect.hpp"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <iostream>
#include <nlohmann/json.hpp>
#include <vector>

namespace ecs {

class MapComponent : public Component {
public:
  sf::RenderTexture renderTexture;
  sf::Sprite sprite;
  std::vector<std::vector<int>> tiles;
  std::vector<sf::IntRect> tileRects;
  sf::Texture spriteSheet;
  std::string spriteSheetPath;
  int tileSize;

  MapComponent(std::vector<std::vector<int>> tiles, std::vector<sf::IntRect> tileRects,
               const std::string &spriteSheetPath, int tileSize)
      : tiles(tiles), tileRects(tileRects), tileSize(tileSize) {
    renderTexture.create(tiles[0].size() * tileSize, tiles.size() * tileSize);
    bool result = spriteSheet.loadFromFile(spriteSheetPath);
    sprite.setTexture(spriteSheet);
    for (int y = 0; y < tiles.size(); y++) {
      for (int x = 0; x < tiles[y].size(); x++) {
        sprite.setTextureRect(tileRects[tiles[y][x]]);
        sprite.setPosition(x * tileSize, y * tileSize);
        renderTexture.draw(sprite);
      }
    }
    renderTexture.display();
    sf::IntRect reset;
    auto size = renderTexture.getTexture().getSize();
    reset.width = size.x;
    reset.height = size.y;
    sprite.setTextureRect(reset);
    sprite.setTexture(renderTexture.getTexture());
  }

  MapComponent(const nlohmann::json &j)
      : MapComponent(j.at("tiles").get<std::vector<std::vector<int>>>(),
                     j.at("tileRects").get<std::vector<sf::IntRect>>(), j.at("spriteSheetPath").get<std::string>(),
                     j.at("tileSize").get<int>()) {
  }

  friend void to_json(nlohmann::json &j, const MapComponent &m) {
    j = nlohmann::json({{"spriteSheetPath", m.spriteSheetPath},
                        {"tileSize", m.tileSize},
                        {"tiles", m.tiles},
                        {"tileRects", m.tileRects}});
  }
};
} // namespace ecs
