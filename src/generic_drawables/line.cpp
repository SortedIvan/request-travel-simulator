#include "line.hpp"

Line::Line(sf::Vector2f pointA, sf::Vector2f pointB, sf::Color lineColor) {
	points = sf::VertexArray(sf::Lines, 2);
	this->lineColor = lineColor;

	points[0].position = pointA;
	points[1].position = pointB;
	points[0].color = lineColor;
	points[1].color = lineColor;
}

void Line::draw(sf::RenderWindow& window) {
	window.draw(points);
}

void Line::setNewPoints(sf::Vector2f pointA, sf::Vector2f pointB) {
	points[0].position = pointA;
	points[1].position = pointB;
}

void Line::move(sf::Vector2f moveBy) {
	points[0].position += moveBy;
	points[1].position += moveBy;
}

void Line::setColor(sf::Color color) {
	lineColor = color;
	points[0].color = color;
	points[1].color = color;
}
