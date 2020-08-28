#include "GameObject.hpp"
GameObject::GameObject(sf::Vector2f& size, sf::Vector2f& position, sf::Color color, sf::Vector2i& tablePos, bool status) {
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
void GameObject::ReduceOpacityBy(int number) {
	_opacity -= number;
	auto col = GetColor();
	rectangle.setFillColor(sf::Color(col.r, col.g, col.b, _opacity));
}
void GameObject::draw(sf::RenderWindow& window) {
	window.draw(rectangle);
}
void GameObject::SetColor(sf::Color newColor) {
	rectangle.setFillColor(newColor);
}
sf::Color GameObject::GetColor() {
	return rectangle.getFillColor();
}
sf::Vector2f GameObject::getInstantPosition() {
	return rectangle.getPosition();

}
void GameObject::setIndices(sf::Vector2i& newIndices) {
	tablePosition.x = newIndices.x;
	tablePosition.y = newIndices.y;
}
void GameObject::setPosition(sf::Vector2f& position) {
	rectangle.setPosition(position);
}