#include "Tile.hpp"
Tile::Tile(sf::Vector2f& size, sf::Vector2f& position, sf::Color color, sf::Vector2i& tablePos, bool status) {
	rectangle.setSize(size);
	rectangle.setPosition(position);
	rectangle.setFillColor(color);
	rectangle.setOutlineColor(sf::Color::Black);
	rectangle.setOutlineThickness(1);
	tablePosition.x = tablePos.x;
	tablePosition.y = tablePos.y;
	_inCombination = status;
	_opacity = 255;
}
void Tile::ReduceOpacityBy(int number) {
	_opacity -= number;
	auto col = GetColor();
	rectangle.setFillColor(sf::Color(col.r, col.g, col.b, _opacity));
}
void Tile::draw(sf::RenderWindow& window) {
	window.draw(rectangle);
}
void Tile::SetColor(sf::Color newColor) {
	rectangle.setFillColor(newColor);
}
sf::Color Tile::GetColor() {
	return rectangle.getFillColor();
}
sf::Vector2f Tile::getInstantPosition() {
	return rectangle.getPosition();

}
void Tile::setIndices(sf::Vector2i& newIndices) {
	tablePosition.x = newIndices.x;
	tablePosition.y = newIndices.y;
}
void Tile::setPosition(sf::Vector2f& position) {
	rectangle.setPosition(position);
}