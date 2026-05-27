#pragma once
#include "SFML/Graphics.hpp"

class Request {
private:
	sf::RectangleShape shape;
	sf::Vector2f position;
	sf::Vector2f destinationPosition;
	sf::Vector2f direction;
	bool isMoving = false;
	float moveSpeed = 0.25f;
	int lastNodePassedThrough;
public:
	Request();
	Request(const sf::Color color, const int width, const int length,
		const sf::Vector2f startingPosition, sf::Vector2f destinationPosition, int lastNodePassedThrough);
	~Request();
	sf::Vector2f getPosition();
	int getLastNodePassedThrough();
	void lerpTowards(sf::Vector2f& position, float deltaTime);
	void move(const sf::Vector2f displacement);
	void draw(sf::RenderWindow& window);
	void update(float deltaTime);
	sf::Color getColor();
};