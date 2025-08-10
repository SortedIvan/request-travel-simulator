#pragma once
#include "SFML/Graphics.hpp"

class Line {
private:
	sf::VertexArray points;
	sf::Color lineColor;
public:
	Line(sf::Vector2f pointA, sf::Vector2f pointB, sf::Color lineColor);
	void draw(sf::RenderWindow& window);
	void setNewPoints(sf::Vector2f pointA, sf::Vector2f pointB);
	void move(sf::Vector2f moveBy);
	void setColor(sf::Color color);
};