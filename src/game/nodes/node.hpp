#pragma once
#include <vector>
#include <unordered_map>
#include "../src/generic_drawables/point.hpp"
#include "../src/game/requests/request.hpp"
#include "../src/game/connectives/connective.hpp"
#include "node_utils.hpp"

class NodeManager;

class Node {
protected:
	NodeManager* nodeManager = nullptr; // Bad practice, but I just wanna move things forward :P

	std::vector<std::unique_ptr<Request>> requests;
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

	virtual void update(float deltaTime);
	virtual void executeNodeBehavior(float deltaTime);
};

class ProducerNode : public Node {
private:
	int connectiveIndex = 0;
	float rateOfProductionMs = 3000.f; // 3000 milliseconds by default
	float timeUntilProduction = 3000.f;
	bool produceSwitch = false;
public:
    ProducerNode(int id, const NodeCreateArgs& args, sf::Font& font, sf::Color color, NodeManager* nodeManager)
        : Node(id, args, font, color, nodeManager) {}
    void update(float deltaTime) override;
    void executeNodeBehavior(float deltaTime) override;
};

class ConsumerNode : public Node {
public:
    ConsumerNode(int id, const NodeCreateArgs& args, sf::Font& font, sf::Color color, NodeManager* nodeManager)
        : Node(id, args, font, color, nodeManager) {}
    void update(float deltaTime) override;
    void executeNodeBehavior(float deltaTime) override;
};