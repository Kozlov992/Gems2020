#include "Tile.hpp"
Tile::Tile(const sf::Vector2f& size, const sf::Vector2f& position, const sf::Color& color, const sf::Vector2i& tablePos, bool status) {
	rectangle.setSize(size);
	rectangle.setPosition(position);
	rectangle.setFillColor(color);
	rectangle.setOutlineColor(sf::Color::Black);
	rectangle.setOutlineThickness(OUTLINE_THICKNESS);
	tablePosition.x = tablePos.x;
	tablePosition.y = tablePos.y;
	_inCombination = status;
	_opacity = 255;	//255 is a maximum possible opacity of a graphical element
}
void Tile::ReduceOpacityBy(int number) {
	_opacity -= number;
	auto col = GetColor();
	rectangle.setFillColor(sf::Color(col.r, col.g, col.b, _opacity));
}
void Tile::draw(sf::RenderWindow& window) {
	window.draw(rectangle);
}
void Tile::SetColor(const sf::Color& newColor) {
	rectangle.setFillColor(newColor);
}
void Tile::setIndices(const sf::Vector2i& newIndices) {
	tablePosition.x = newIndices.x;
	tablePosition.y = newIndices.y;
}
void Tile::setPosition(const sf::Vector2f& position) {
	rectangle.setPosition(position);
}