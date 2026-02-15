#pragma once
#include "SFML/Graphics.hpp"

class Request {
private:
	sf::RectangleShape shape;
	sf::Vector2f position;
	bool isMoving = false;
public:
	Request();
	Request(const sf::Color color, const int width, const int length, const sf::Vector2f startingPosition);
	~Request();
	sf::Vector2f getPosition();
	void lerpTowards(sf::Vector2f& position, float deltaTime);
	void move(const sf::Vector2f displacement);
	void draw(sf::RenderWindow& window);
	void update(float deltaTime);
};