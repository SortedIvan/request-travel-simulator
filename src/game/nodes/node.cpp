#include "node.hpp"
#include "../../utils/logger.hpp"
#include "../nodes/node_manager.hpp" 
#include "../src/utils/global_state.hpp"

Node::Node(int id, const NodeCreateArgs& nodeCreateArgs, sf::Font& nodeLabelFont,
	sf::Color& nodeLabelFillColor, NodeManager* nodeManager) {
	this->id = id;
	this->nodeType = nodeCreateArgs.nodeType;
	this->nodeShape = Point(
		nodeCreateArgs.position, nodeCreateArgs.nodeShapeSize, nodeCreateArgs.nodeColor
	);
	this->nodeManager = nodeManager;

	const float nodeSelectedShapeSize = nodeCreateArgs.nodeShapeSize - nodeCreateArgs.nodeShapeSize / 10.f;

	this->nodeSelectedShape = Point(
		nodeCreateArgs.position, nodeSelectedShapeSize, sf::Color::Transparent
	);

	this->nodeSelectedShape.getCircleShape().setOutlineColor(sf::Color::Black);
	this->nodeSelectedShape.getCircleShape().setOutlineThickness(2.f);

	setNodeLabel(nodeLabelFont, nodeLabelFillColor);

	this->nodeQueueSizeLabel.setFont(nodeLabelFont);
	this->nodeQueueSizeLabel.setFillColor(sf::Color::White);
	this->nodeQueueSizeLabel.setCharacterSize(nodeLabelSize);

	const sf::Vector2f labelPosition = sf::Vector2f(
		nodeShape.getPosition().x - (nodeQueueSizeLabel.getLocalBounds().width / 2) - 2,
		(nodeShape.getPosition().y - (nodeQueueSizeLabel.getLocalBounds().height / 2)) + this->nodeSelectedShape.getCircleShape().getRadius() * 1.5f
	);

	this->nodeQueueSizeLabel.setPosition(labelPosition);

}

Node::Node(NodeManager* nodeManager){
	this->nodeManager = nodeManager;
}

void Node::draw(sf::RenderWindow& window) {
	nodeShape.draw(window);
	window.draw(nodeLabel);

	for (int i = 0; i < nodeConnections.size(); ++i) {
		nodeConnections[i].draw(window);
	}

	if (isSelected) {
		nodeSelectedShape.draw(window);
	}

	if (drawNodeQueueSize) {
		nodeQueueSizeLabel.setString(std::to_string(requests.size()));
		window.draw(nodeQueueSizeLabel);
	}
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

void Node::setIsSelected(bool isSelected) {
	this->isSelected = isSelected;
}

bool Node::getIsSelected() {
	return this->isSelected;
}

bool Node::checkCollisionWithinNode(sf::Vector2f point) {
	auto nodeRadius = this->getNodeShape().getCircleShape().getRadius();
	auto nodeCenter = this->getNodeShape().getCircleShape().getPosition();

	auto xComponent = (point.x - nodeCenter.x) * (point.x - nodeCenter.x);
	auto yComponent = (point.y - nodeCenter.y) * (point.y - nodeCenter.y);

	return xComponent + yComponent <= nodeRadius * nodeRadius;
}

void Node::checkForRequestCollision() {
	if (!GlobalState::getSimulationOn()) {
		return;
	}

	auto& requests = nodeManager->getRequests();

	for (auto it = requests.begin(); it != requests.end();) {
		if ((*it)->getLastNodePassedThrough() == this->getId()) {
			++it;
			continue;
		}

		if (checkCollisionWithinNode((*it)->getPosition())) {
			this->requests.push(std::move(*it));
			it = requests.erase(it);
		}
		else {
			++it;
		}
	}
}

void Node::clearRequests(std::queue<std::unique_ptr<Request>>& requests) {
	std::queue<std::unique_ptr<Request>> empty;
	std::swap(requests, empty);
}