#include "node_manager.hpp"
#include <iostream>
#include "../../utils/logger.hpp"

NodeManager::NodeManager() {

}

NodeManager::~NodeManager() {

}


bool NodeManager::checkIfIdValid(int id) {
	if (id >= nodes.size() || id < 0 || nodes[id] == nullptr) {
		return false;
	}
	return true;
}

void NodeManager::draw(sf::RenderWindow& window) {
	for (int i = 0; i < nodes.size(); ++i) {
		nodes[i]->draw(window);
	}
}

void NodeManager::update(float deltaTime) {
	for (int i = 0; i < nodes.size(); ++i) {
		nodes[i]->update(deltaTime);
	}
}

const std::vector<std::unique_ptr<Node>>& NodeManager::getNodesView() {
	return this->nodes;
}

std::vector<std::unique_ptr<Node>>& NodeManager::getNodesModifiable() {
	return this->nodes;
}

int NodeManager::getNodeId() {
	int id = 0;
	if (!idStack.empty()) {
		id = idStack.top();
		idStack.pop();
	}
	else {
		id = nodeIdCounter++;
	}
	return id;
}

void NodeManager::addNode(std::unique_ptr<Node> node) {
	int id = getNodeId();

	if (nodes.size() <= id) {
		nodes.push_back(std::move(node));
	}
	else {
		nodes[id] = std::move(node);
	}
}

int NodeManager::addNode(NodeType nodeType, int nodeShapeSize, const sf::Vector2f position, 
	sf::Color nodeColor = sf::Color::White) {
	
	int id = getNodeId();
	auto node = std::make_unique<Node>(nodeType, id, nodeShapeSize, position, nodeColor);

	if (nodes.size() <= id) {
		nodes.push_back(std::move(node));
	}
	else {
		nodes[id] = std::move(node);
	}

	return id;
}

void NodeManager::removeNode(int id) {
	if (!checkIfIdValid(id)) { return; }
	nodes[id] = nullptr;
	idStack.push(id);
}

bool NodeManager::checkIfConnectionExists(int nodeFrom, int nodeTo) {
	for (int i = 0; i < nodes[nodeFrom]->getNodeConnections().size(); ++i) {
		auto nodeFromToPair = nodes[nodeFrom]->getNodeConnections()[i].getNodeFromAndTo();

		if (nodeFromToPair.second->getId() == nodeTo) {
			return true;
		}
	}

	return false;
}

void NodeManager::connectTwoNodes(int nodeFrom, int nodeTo) {
	if (!checkIfIdValid(nodeFrom)) { return; }
	if (!checkIfIdValid(nodeTo)) { return; }
	if (checkIfConnectionExists(nodeFrom, nodeTo)) { return; }

	Logger::info(__FILE__,__LINE__, "Attempting to connect node " + std::to_string(nodeFrom) + "to node" + std::to_string(nodeTo));

	// Connective contains std::vector<unique_ptr>> which is NON-COPYABLE
	// thus, we need to emplace back here directly
	nodes[nodeFrom]->getNodeConnections().emplace_back(
		nodes[nodeFrom].get(), nodes[nodeTo].get(), defaultConnectiveColor
	);

}
