#include "point.hpp"

Point::Point(sf::Vector2f position, float radius, sf::Color fillColor) {
	shape = sf::CircleShape(radius);
	shape.setOrigin(sf::Vector2f(radius, radius));
	shape.setPosition(position);
	shape.setFillColor(fillColor);
}

Point::Point() {

}

void Point::draw(sf::RenderWindow& window) {
	window.draw(this->shape);
}

void Point::move(sf::Vector2f displacement) {
	shape.setPosition(shape.getPosition() + displacement);
}

sf::Vector2f Point::getPosition() {
	return shape.getPosition();
}

sf::CircleShape& Point::getCircleShape() {
	return shape;
}