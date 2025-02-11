#include "IntRect.hpp"
#include <SFML/Graphics/Rect.hpp>

namespace sf {

void to_json(nlohmann::json &j, const IntRect &i) {
  j = nlohmann::json({{"left", i.position.x}, {"top", i.position.y}, {"width", i.size.x}, {"height", i.size.y}});
}

void from_json(const nlohmann::json &j, IntRect &i) {
  j.at("top").get_to(i.position.y);
  j.at("left").get_to(i.position.x);
  j.at("width").get_to(i.size.x);
  j.at("height").get_to(i.size.y);
}

} // namespace sf
