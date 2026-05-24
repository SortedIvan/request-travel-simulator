#pragma once
#include <vector>
#include <unordered_map>
#include "../src/generic_drawables/point.hpp"
#include "../src/game/requests/request.hpp"
#include "../src/game/connectives/connective.hpp"
#include "../src/math_utils/generic_math.hpp"
#include "node_utils.hpp"
#include <queue>

class NodeManager;

class Node {
protected:
	NodeManager* nodeManager = nullptr; // Bad practice, but I just wanna move things forward :P

	std::queue<std::unique_ptr<Request>> requests;
	std::vector<Connective> nodeConnections;
	Point nodeShape; // for now, all nodes will be a simple point
	Point nodeSelectedShape;
	NodeType nodeType;
	sf::Text nodeLabel;	
	int requestsProcessed = 0;
	int id;
	const int nodeLabelSize = 15;
	bool isActive = true;
	bool isSelected = false;	

	// Every node has a set amount of time until it executes its behavior
	float rateOfActionMs = 3000.f;
	float timeUntilAction = 3000.f;
	bool actionSwitch = false;

	void setNodeLabel(sf::Font& nodeLabelFont, const sf::Color& nodeLabelColor);

public:
    virtual ~Node() = default;
	Node(NodeManager* nodeManager);
	Node(int id, const NodeCreateArgs& nodeCreateArgs,
		sf::Font& nodeLabelFont, sf::Color& nodeLabelFillColor, NodeManager* nodeManager);
	void draw(sf::RenderWindow& window);
	Point getNodeShape();
	int getId();
	void setId(int newId);
	std::vector<Connective>& getNodeConnections();
	void setIsSelected(bool isSelected);
	bool getIsSelected();

	bool checkCollisionWithinNode(sf::Vector2f point);
	void checkForRequestCollision();
	void clearRequests(std::queue<std::unique_ptr<Request>>& requests);

	virtual void update(float deltaTime);
	virtual void executeNodeBehavior(float deltaTime);
};

class ProducerNode : public Node {
private:
	int connectiveIndex = 0;
public:
    ProducerNode(int id, const NodeCreateArgs& args, sf::Font& font, sf::Color color, NodeManager* nodeManager)
        : Node(id, args, font, color, nodeManager) 
	{
		this->rateOfActionMs = GenericMath::getRandomFloat(1000.f, 2000.f);
		this->actionSwitch = false;
	}
    void update(float deltaTime) override;
};

class SplitterNode : public Node {
private:
	int numberOfConnectionsToSplitTo = 2; // Default to 2
	int splitterConnectionIndex = 0; // start from the first connection

public:
	SplitterNode(int id, const NodeCreateArgs& args, sf::Font& font, sf::Color color, NodeManager* nodeManager)
		: Node(id, args, font, color, nodeManager) {}
	void update(float deltaTime) override;
};

class MergerNode : public Node {
	MergerNode(int id, const NodeCreateArgs& args, sf::Font& font, sf::Color color, NodeManager* nodeManager)
		: Node(id, args, font, color, nodeManager) {
	}
	void update(float deltaTime) override;
};