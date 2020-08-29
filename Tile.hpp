#pragma once
#include <SFML/Graphics.hpp>
class Tile {
private:
	sf::RectangleShape rectangle;
	sf::Vector2i tablePosition;
	bool _inCombination;
	int _opacity;
public:
	int Opacity() { return _opacity; }
	void ReduceOpacityBy(int number);
	void AddInCombination() { _inCombination = true; }
	bool InCombination() { return _inCombination; }
	void DeleteFromCombination() { _inCombination = false; }
	void SetColor(sf::Color newColor);
	sf::Color GetColor();
	sf::Vector2f getInstantPosition();
	sf::Vector2i getTableIndices() { return tablePosition; }
	void setPosition(sf::Vector2f& position);
	void draw(sf::RenderWindow& window);
	void setIndices(sf::Vector2i& newIndices);
	Tile(sf::Vector2f& size, sf::Vector2f& position, sf::Color color, sf::Vector2i& tablePos, bool status = false);
};