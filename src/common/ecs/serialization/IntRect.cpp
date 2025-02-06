#include "IntRect.hpp"
#include <SFML/Graphics/Rect.hpp>

namespace sf {

void to_json(nlohmann::json &j, const IntRect &i) {
  j = nlohmann::json({{"left", i.left}, {"top", i.top}, {"width", i.width}, {"height", i.height}});
}

void from_json(const nlohmann::json &j, IntRect &i) {
  j.at("top").get_to(i.top);
  j.at("left").get_to(i.left);
  j.at("width").get_to(i.width);
  j.at("height").get_to(i.height);
}

} // namespace sf
