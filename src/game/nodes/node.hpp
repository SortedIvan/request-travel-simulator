#include <vector>
#include <unordered_map>
#include "../src/generic_drawables/point.hpp"
#include "../src/game/requests/request.hpp"
#include "../src/game/connectives/connective.hpp"

enum NodeType {
	NONE,
	PRODUCER,
	CONSUMER,
	DISTRIBUTOR,
	MULTIPLICATOR
};

inline const char* nodeTypeToString(NodeType nt)
{
    switch (nt)
    {
		case NONE:       		return "None";
		case PRODUCER:   		return "P";
        case CONSUMER:   		return "C";
		case DISTRIBUTOR: 		return "D";
		case MULTIPLICATOR: 	return "M";
        default:      return "None";
    }
}

class Node {
private:
	std::vector<std::unique_ptr<Request>> requests;
	std::vector<Connective> nodeConnections;
	Point nodeShape; // for now, all nodes will be a simple point
	NodeType nodeType;
	sf::Text nodeLabel;	
	int requestsProcessed = 0;
	int id;
	bool isActive = true;
	const int nodeLabelSize = 15;

	void setNodeLabel(sf::Font& nodeLabelFont, const sf::Color& nodeLabelColor);

public:
	~Node();
	Node();
	Node(NodeType nodeType, int id, int nodeShapeSize,
		const sf::Vector2f position, sf::Color nodeColor,
		sf::Font& nodeLabelFont, sf::Color& nodeLabelFillColor);
	void draw(sf::RenderWindow& window);
	bool hasRequests();
	void addRequest(std::unique_ptr<Request> request);
	Point getNodeShape();
	int getId();
	void setId(int newId);
	std::vector<Connective>& getNodeConnections();
	std::vector<std::unique_ptr<Request>>& getNodeRequests();

	virtual void update(float deltaTime);
	virtual void executeNodeBehavior(float deltaTime);
};

class ProducerNode : public Node {
public:
    void update(float deltaTime) override;
    void executeNodeBehavior(float deltaTime) override;
};

class ConsumerNode : public Node {
public:
    void update(float deltaTime) override;
    void executeNodeBehavior(float deltaTime) override;
};