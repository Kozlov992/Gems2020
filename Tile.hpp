#pragma once
#include <SFML/Graphics.hpp>
class Tile {
private:
	sf::RectangleShape rectangle;
	sf::Vector2i tablePosition;
	bool _inCombination;
	int _opacity;
public:
	int Opacity() const { return _opacity; }
	void ReduceOpacityBy(int number);
	void AddInCombination() { _inCombination = true; }
	bool InCombination() const { return _inCombination; }
	void DeleteFromCombination() { _inCombination = false; }
	void SetColor(const sf::Color& newColor);
	sf::Color Tile::GetColor() const { return rectangle.getFillColor(); }
	sf::Vector2f Tile::getInstantPosition() const { return rectangle.getPosition(); }
	sf::Vector2i getTableIndices() const { return tablePosition; }
	void setPosition(const sf::Vector2f& position);
	void draw(sf::RenderWindow& window);
	void setIndices(const sf::Vector2i& newIndices);
	Tile(const sf::Vector2f& size, const sf::Vector2f& position, const sf::Color& color, const sf::Vector2i& tablePos, bool status = false);
};