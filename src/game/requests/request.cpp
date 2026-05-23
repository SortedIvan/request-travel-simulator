#include "request.hpp"
#include "../../math_utils/vec_math.hpp"
#include <iostream>

Request::~Request() {

}

Request::Request() {

}

Request::Request(const sf::Color color, const int width, const int length, const sf::Vector2f startingPosition,
	sf::Vector2f destinationPosition, int lastNodePassedThrough) {
	shape = sf::RectangleShape(sf::Vector2f(width, length));
	shape.setPosition(sf::Vector2f(startingPosition.x - (length / 2), startingPosition.y - (width / 2)));
	shape.setFillColor(color);

	this->destinationPosition = destinationPosition;
	this->direction = VecMath::normalize(destinationPosition - startingPosition);
	this->lastNodePassedThrough = lastNodePassedThrough;
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

}

int Request::getLastNodePassedThrough() {
	return this->lastNodePassedThrough;
}

void Request::update(float deltaTime) {
	const auto& oldPos = shape.getPosition();
	const auto& xDisplacement = deltaTime * moveSpeed * direction.x;
	const auto& yDisplacement = deltaTime * moveSpeed * direction.y;
	shape.setPosition(sf::Vector2f(oldPos.x + xDisplacement, oldPos.y + yDisplacement));
}