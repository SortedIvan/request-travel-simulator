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
public:
	~Node();
	Node();
	void draw(sf::RenderWindow& window);
	bool hasRequest();
	void setRequest(std::unique_ptr<Request> request);
	Point getNodeShape();

	virtual void processRequest() {
		// default behavior here
	}
};