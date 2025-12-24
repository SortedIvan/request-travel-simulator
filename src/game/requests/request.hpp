#pragma once
#include "SFML/Graphics.hpp"

class Request {
private:
	sf::RectangleShape shape;
	sf::Vector2f position;
public:
	Request();
	Request(const sf::Color color, const int width, const int length, const sf::Vector2f startingPosition);
	~Request();
	void move(const sf::Vector2f displacement);
	sf::Vector2f getPosition();
	void draw(sf::RenderWindow& window);
};