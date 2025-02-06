#pragma once

#include "Component.hpp"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <nlohmann/json.hpp>
#include <vector>

// Json impl for sf::IntRect
namespace sf {
inline void to_json(nlohmann::json &j, const IntRect &i) {
  j = nlohmann::json({{"left", i.left}, {"top", i.top}, {"width", i.width}, {"height", i.height}});
}

inline void from_json(const nlohmann::json &j, IntRect &i) {
  j.at("top").get_to(i.top);
  j.at("left").get_to(i.left);
  j.at("width").get_to(i.width);
  j.at("height").get_to(i.height);
}

} // namespace sf
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
    spriteSheet.loadFromFile(spriteSheetPath);
    sprite.setTexture(spriteSheet);
    for (int y = 0; y < tiles.size(); y++) {
      for (int x = 0; x < tiles[y].size(); x++) {
        sprite.setTextureRect(tileRects[tiles[y][x]]);
        sprite.setPosition(x * tileSize, y * tileSize);
        renderTexture.draw(sprite);
      }
    }
    renderTexture.display();
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
