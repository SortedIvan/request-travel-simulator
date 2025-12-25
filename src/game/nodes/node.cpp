#include "node.hpp"
#include "../../utils/logger.hpp"

Node::Node(NodeType nodeType, int id, int nodeShapeSize, 
	const sf::Vector2f position, sf::Color nodeColor, sf::Font& nodeLabelFont,
	sf::Color& nodeLabelFillColor) {
	this->id = id;
	this->nodeType = nodeType;
	this->nodeShape = Point(
		position, nodeShapeSize, nodeColor
	);

	setNodeLabel(nodeLabelFont, nodeLabelFillColor);
}

Node::~Node() {

}

Node::Node(){

}

void Node::draw(sf::RenderWindow& window) {
	nodeShape.draw(window);
	window.draw(nodeLabel);

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

std::vector<std::unique_ptr<Request>>& Node::getNodeRequests() {
	return this->requests;
}

void Node::setNodeLabel(sf::Font& nodeLabelFont, const sf::Color& nodeLabelColor) {
	if (this->nodeType == NodeType::NONE) {
		return;
	}

	this->nodeLabel.setFont(nodeLabelFont);
	this->nodeLabel.setFillColor(nodeLabelColor);
	this->nodeLabel.setCharacterSize(nodeLabelSize);
	this->nodeLabel.setString(nodeTypeToString(this->nodeType));

	const sf::Vector2f labelPosition = sf::Vector2f(
		nodeShape.getPosition().x - (nodeLabel.getLocalBounds().width / 2),
		nodeShape.getPosition().y - (nodeLabel.getLocalBounds().height / 2)
	);

	this->nodeLabel.setPosition(labelPosition);
}