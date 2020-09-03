#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "GameParamerts.hpp"
namespace support {
	bool IsIn(const sf::Vector2i& position, const std::vector<sf::Vector2i>& vector);
	std::vector<sf::Vector2i> FindUnion(const std::vector<sf::Vector2i>& vector1, const std::vector<sf::Vector2i>& vector2);
	bool IsOutOfBounds(const sf::Vector2i& position);
}