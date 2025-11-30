#include "../src/math_utils/vec_math.hpp"
#include "./connective.hpp"

Connective::Connective(Node* nodeFrom, Node* nodeTo, const sf::Color connectiveColor) {
	this->nodeFrom = nodeFrom;
	this->nodeTo = nodeTo;
	this->connectiveColor = connectiveColor;
	initializeConnectiveDrawable();
}

Connective::~Connective() {};

bool Connective::isActive() {
	return active;
}

void Connective::setIsActive(bool isActive) {
	this->active = isActive;
}

void Connective::draw(sf::RenderWindow& window) {
	connectiveLine.draw(window);
	window.draw(connectiveEnd);
}

void Connective::move() {
	initializeConnectiveDrawable();
}

void Connective::incrementRequestsPassedThrough() {
	this->requestsPassedThrough++;
}

int Connective::getRequestsPassedThrough() {
	return this->requestsPassedThrough;
}

void Connective::initializeConnectiveDrawable() {
	// first, reinitialize the lines based on the new positions of the nodes 
	Point nodeFromShape = nodeFrom->getNodeShape();
	Point nodeToShape = nodeTo->getNodeShape();
	
	// we want to start the lines at the "edge" of the node, so it would be somethign like:
	// nodeCenter + directionToOtherNode * radius
	
	sf::Vector2f displacementFromTo = nodeToShape.getPosition() - nodeFromShape.getPosition();
	sf::Vector2f directionVector = VecMath::normalize(displacementFromTo);
	sf::Vector2f startPoint = nodeFromShape.getPosition() + directionVector * nodeFromShape.getCircleShape().getRadius();
	sf::Vector2f endPoint = nodeToShape.getPosition() + VecMath::inverse(directionVector) * nodeToShape.getCircleShape().getRadius();

	connectiveLine.initializeLinesArray(startPoint, endPoint);
	
	sf::ConvexShape triangle;
	triangle.setPointCount(3); 

	sf::Vector2f triangleBottomLeft = VecMath::applyRotation(45.f, VecMath::inverse(directionVector)) * connectiveEndSideLength + endPoint;
	sf::Vector2f triangleBottomRight = VecMath::applyRotation(-45.f, VecMath::inverse(directionVector)) * connectiveEndSideLength + endPoint;

	triangle.setPoint(0, endPoint); // top
	triangle.setPoint(1, triangleBottomLeft); 
	triangle.setPoint(2, triangleBottomRight);

	triangle.setFillColor(connectiveColor);
	triangle.setOutlineColor(sf::Color::Black);
	triangle.setOutlineThickness(2.f);

	this->connectiveEnd = triangle;
}
