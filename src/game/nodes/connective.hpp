#pragma once
#include <vector>
#include "../src/generic_drawables/dashed_line.hpp"

class Node;

class Connective {
private:
	bool active = true;
	int requestsPassedThrough = 0;
	float connectiveEndSideLength = 15.f;
	Node* nodeFrom;
	Node* nodeTo;
	DashedLine connectiveLine;
	sf::ConvexShape connectiveEnd;
	sf::Color connectiveColor;

	void initializeConnectiveDrawable();
	void initializeConnectiveDrawableDummy(sf::Vector2f from, sf::Vector2f to);
public:
	~Connective();
	Connective(Node* nodeFrom, Node* nodeTo, const sf::Color connectiveColor);
	Connective(const sf::Vector2f positionFrom, const sf::Vector2f positionTo, const sf::Color connectiveColor);
	bool isActive();
	void setIsActive(const bool isActive);
	void draw(sf::RenderWindow& window);
	void move();
	void incrementRequestsPassedThrough();
	int getRequestsPassedThrough();
};