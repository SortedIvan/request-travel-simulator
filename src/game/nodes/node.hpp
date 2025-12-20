#include <vector>
#include <unordered_map>
#include "../src/generic_drawables/point.hpp"
#include "../src/game/requests/request.hpp"
#include "../src/game/nodes/connective.hpp"

enum NodeType {
	PRODUCER,
	CONSUMER,
	DISTRIBUTOR,
	MULTIPLICATOR
};

class Node {
private:
	Point nodeShape; // for now, all nodes will be a simple point
	NodeType nodeType;
	std::unique_ptr<Request> request;
	int requestsProcessed = 0;
	bool isActive = true;
	std::vector<Connective> nodeConnections;
	int id;
	sf::Text nodeLabel;
public:
	~Node();
	Node();
	Node(NodeType nodeType, int id, int nodeShapeSize,
		const sf::Vector2f position, sf::Color nodeColor);
	void draw(sf::RenderWindow& window);
	bool hasRequest();
	void setRequest(std::unique_ptr<Request> request);
	Point getNodeShape();
	int getId();
	void setId(int newId);
	void addNodeConnection(Connective connection);
	std::vector<Connective>& getNodeConnections();

	virtual void update(float deltaTime);
	virtual void executeNodeBehavior(float deltaTime);
};