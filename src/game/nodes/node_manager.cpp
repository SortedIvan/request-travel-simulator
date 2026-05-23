#include "node_manager.hpp"
#include <iostream>
#include "../../utils/logger.hpp"

NodeManager::NodeManager(sf::Font& nodeLabelFont) : nodeLabelFont(nodeLabelFont) {
	
}

NodeManager::~NodeManager() {

}

bool NodeManager::checkIfIdValid(int id) {
	if (id >= nodes.size() || id < 0 || nodes[id] == nullptr) {
		Logger::warn(__FILE__,__LINE__, "Node id: " + std::to_string(id) + " is not valid");
		return false;
	}
	return true;
}

void NodeManager::draw(sf::RenderWindow& window) {
	for (int i = 0; i < nodes.size(); ++i) {
		nodes[i]->draw(window);
	}

	for (int i = 0; i < requests.size(); ++i) {
		requests[i].get()->draw(window);
	}
}

void NodeManager::update(float deltaTime) {
	for (int i = 0; i < nodes.size(); ++i) {
		nodes[i]->update(deltaTime);
	}

	for (int i = 0; i < requests.size(); ++i) {
		requests[i].get()->update(deltaTime);
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

std::unique_ptr<Node> NodeManager::createNode(const NodeCreateArgs& nodeArgs) {
	int id = getNodeId();
    switch (nodeArgs.nodeType)
    {
        case NodeType::PRODUCER:
            return std::make_unique<ProducerNode>(id, nodeArgs, nodeLabelFont, defaultNodeLabelFillColor, this);

        default:
			return std::make_unique<ProducerNode>(id, nodeArgs, nodeLabelFont, defaultNodeLabelFillColor, this);
    }
}

int NodeManager::addNode(const NodeCreateArgs& nodeCreateArgs) {
	auto node = createNode(nodeCreateArgs);
	const int nodeId = node.get()->getId();

	if (nodes.size() <= nodeId) {
		nodes.push_back(std::move(node));
	}
	else {
		nodes[nodeId] = std::move(node);
	}

	return nodeId;
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
			Logger::warn(__FILE__,__LINE__, "Connection already exists from node: " + std::to_string(nodeFrom) 
				+ " to node: " + std::to_string(nodeTo));
			return true;
		}
	}

	return false;
}

void NodeManager::connectTwoNodes(int nodeFrom, int nodeTo) {
	if (!checkIfIdValid(nodeFrom)) return;
	if (!checkIfIdValid(nodeTo)) return;
	if (checkIfConnectionExists(nodeFrom, nodeTo)) return;

	Logger::info(__FILE__,__LINE__, "Attempting to connect node " + std::to_string(nodeFrom) + "to node" + std::to_string(nodeTo));

	// Connective contains std::vector<unique_ptr<Request>> -> NON-COPYABLE
	// we need to emplace back here directly
	nodes[nodeFrom]->getNodeConnections().emplace_back(
		nodes[nodeFrom].get(), nodes[nodeTo].get(), defaultConnectiveColor
	);

}

Node* NodeManager::getNode(int nodeIndex) {
	if (nodeIndex < 0) return nullptr;
	return nodes[nodeIndex].get();
}

std::vector<std::unique_ptr<Request>>& NodeManager::getRequests() {
	return requests;
}

void NodeManager::addRequest(Request request) {
	requests.push_back(std::make_unique<Request>(request));
}

void NodeManager::removeRequest(int index) {
	requests[index].release();
	requests.erase(requests.begin() + index);
}