#include "node.hpp"
Node::Node(NodeType nodeType, int id, int nodeShapeSize, const sf::Vector2f position, sf::Color nodeColor) {
	this->id = id;
	this->nodeType = nodeType;
	this->nodeShape = Point(
		position, nodeShapeSize, nodeColor
	);
}

Node::~Node() {

}

Node::Node(){

}

void Node::draw(sf::RenderWindow& window) {
	nodeShape.draw(window);

	for (int i = 0; i < nodeConnections.size(); ++i) {
		nodeConnections[i].draw(window);
	}
}

bool Node::hasRequests() {
	return !requests.empty();
}

void Node::addRequest(std::unique_ptr<Request> request) {
	this->requests.push_back(std::move(request));
}

Point Node::getNodeShape() {
	return this->nodeShape;
}

void Node::update(float deltaTime) {
	// default update behavior
}

void Node::executeNodeBehavior(float deltaTime) {
	// default node behavior
}

int Node::getId() {
	return this->id;
}

void Node::setId(int newId) {
	this->id = newId;
}

std::vector<Connective>& Node::getNodeConnections() {
	return this->nodeConnections;
}