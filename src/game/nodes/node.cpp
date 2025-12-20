//#include <vector>
//#include <unordered_map>
//#include "../src/generic_drawables/point.hpp"
//#include "../src/game/requests/request.hpp"
//#include "../src/game/nodes/connective.hpp"
//
//enum NodeType {
//	PRODUCER,
//	CONSUMER,
//	DISTRIBUTOR,
//	MULTIPLICATOR
//};
//
//class Node {
//private:
//	Point nodeShape; // for now, all nodes will be a simple point
//	NodeType nodeType;
//	std::unique_ptr<Request> request;
//	int requestsProcessed = 0;
//	bool isActive = true;
//	std::vector<Connective> nodeConnections;
//public:
//	~Node();
//	Node();
//	void draw(sf::RenderWindow& window);
//	bool hasRequest();
//	void setRequest(std::unique_ptr<Request> request);
//	Point getNodeShape();
//
//	virtual void processRequest();
//};
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

bool Node::hasRequest() {
	return request != nullptr;
}

void Node::setRequest(std::unique_ptr<Request> request) {
	this->request = std::move(request);
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

void Node::addNodeConnection(Connective connection) {
	nodeConnections.push_back(connection);
}

std::vector<Connective>& Node::getNodeConnections() {
	return this->nodeConnections;
}