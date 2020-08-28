#include "SupportingFunctions.hpp"
bool support::IsIn(sf::Vector2i& position, std::vector<sf::Vector2i>& vector) {
	if (vector.empty())
		return false;
	for (auto element : vector) {
		if (element.x == position.x && element.y == position.y)
			return true;
	}
	return false;
}
bool support::IsOutOfBounds(sf::Vector2i& position) {
	return (position.x < 0 || position.y < 0) || (position.x >= TABLE_HEIGHT || position.y >= TABLE_WIDTH);
}
std::vector<sf::Vector2i> support::FindUnion(std::vector<sf::Vector2i>& vector1, std::vector<sf::Vector2i>& vector2) {
	std::vector<sf::Vector2i> answer;
	if (vector1.empty()) {
		answer = vector2;
		return answer;
	}
	answer = vector1;
	for (auto element : vector2) {
		if (!support::IsIn(element, vector1))
			answer.push_back(element);
	}
	return answer;
}