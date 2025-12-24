#include "request.hpp"

Request::~Request() {

}

Request::Request() {

}

Request::Request(const sf::Color color, const int width, const int length, const sf::Vector2f startingPosition) {
	shape = sf::RectangleShape(sf::Vector2f(width, length));
	shape.setPosition(startingPosition);
	shape.setFillColor(color);
}

void Request::move(const sf::Vector2f displacement) {
	shape.setPosition(shape.getPosition() + displacement);
}

sf::Vector2f Request::getPosition() {
	return shape.getPosition();
}

void Request::draw(sf::RenderWindow& window) {
	window.draw(shape);
}
