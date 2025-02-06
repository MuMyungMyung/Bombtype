#pragma once

#include <SFML/Graphics/Rect.hpp>
#include <nlohmann/json.hpp>

// Json impl for sf::IntRect
namespace sf {

void to_json(nlohmann::json &j, const IntRect &i);
void from_json(const nlohmann::json &j, IntRect &i);

} // namespace sf
