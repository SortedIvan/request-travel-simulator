#include <vector>
#include <unordered_map>
#include "../src/generic_drawables/point.hpp"
#include "../src/game/requests/request.hpp"
#include "../src/game/connectives/connective.hpp"
#include "node_utils.hpp"

class Node {
private:
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
	Node();
	Node(int id, const NodeCreateArgs& nodeCreateArgs,
		sf::Font& nodeLabelFont, sf::Color& nodeLabelFillColor);
	void draw(sf::RenderWindow& window);
	bool hasRequests();
	void addRequest(std::unique_ptr<Request> request);
	Point getNodeShape();
	int getId();
	void setId(int newId);
	std::vector<Connective>& getNodeConnections();
	std::vector<std::unique_ptr<Request>>& getNodeRequests();
	void setIsSelected(bool isSelected);
	bool getIsSelected();

	virtual void update(float deltaTime);
	virtual void executeNodeBehavior(float deltaTime);
};

class ProducerNode : public Node {
public:
    ProducerNode(int id, const NodeCreateArgs& args, sf::Font& font, sf::Color color)
        : Node(id, args, font, color) {}
    void update(float deltaTime) override;
    void executeNodeBehavior(float deltaTime) override;
};

class ConsumerNode : public Node {
public:
    ConsumerNode(int id, const NodeCreateArgs& args, sf::Font& font, sf::Color color)
        : Node(id, args, font, color) {}
    void update(float deltaTime) override;
    void executeNodeBehavior(float deltaTime) override;
};