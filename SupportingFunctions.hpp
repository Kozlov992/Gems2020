#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "GameParamerts.hpp"
namespace support {
	bool IsIn(sf::Vector2i& position, std::vector<sf::Vector2i>& vector);
	std::vector<sf::Vector2i> FindUnion(std::vector<sf::Vector2i>& vector1, std::vector<sf::Vector2i>& vector2);
	bool IsOutOfBounds(sf::Vector2i& position);
}