#pragma once
#include <vector>
#include "../requests/request.hpp"
#include "../src/generic_drawables/dashed_line.hpp"

class Node;

class Connective {
private:
	std::vector<std::unique_ptr<Request>> currentRequests;
	bool active = true;
	int requestsPassedThrough = 0;
	float connectiveEndSideLength = 15.f;
	Node* nodeFrom;
	Node* nodeTo;
	DashedLine connectiveLine;
	sf::ConvexShape connectiveEnd;
	sf::Color connectiveColor;

	void initializeConnectiveDrawable();
public:
	~Connective();
	Connective();
	Connective(const Connective&) = delete;
	Connective& operator=(const Connective&) = delete;
	Connective(Node* nodeFrom, Node* nodeTo, const sf::Color connectiveColor);
	Connective(const sf::Vector2f positionFrom, const sf::Vector2f positionTo, const sf::Color connectiveColor);
	Connective(Connective&&) noexcept = default;
	Connective& operator=(Connective&&) noexcept = default;

	void initializeConnectiveDrawableDummy(sf::Vector2f from, sf::Vector2f to);
	bool isActive();
	void setIsActive(const bool isActive);
	void draw(sf::RenderWindow& window);
	void update(float deltaTime);
	void move();
	void incrementRequestsPassedThrough();
	int getRequestsPassedThrough();
	void addRequest(std::unique_ptr<Request> request);
	std::pair<Node*, Node*> getNodeFromAndTo();
	void setConnectiveColor(sf::Color color);
};