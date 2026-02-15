#include "request.hpp"
//#include "../math_utils/generic_math.hpp"

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

void Request::lerpTowards(sf::Vector2f& position, float deltaTime) {
    // float new_x = GenericMath::lerp(shape.getPosition().x, position.x, 1 - std::pow(0.5, deltaTime));
    // float new_y = GenericMath::lerp(shape.getPosition().y, position.y, 1 - std::pow(0.5, deltaTime));
    //shape.setPosition(new_x, new_y);
}

void Request::update(float deltaTime) {
	//if (shape.getLocalBounds().intersects())
}