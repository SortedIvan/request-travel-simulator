#include "../src/generic_drawables/point.hpp"

enum NodeType {
	PRODUCER,
	CONSUMER,
	DISTRIBUTOR,
	MULTIPLICATOR
};

class Node {
private:
	Point* nodeShape; // for now, all nodes will be a simple point
	NodeType nodeType;
	bool hasRequest = false; // true if there is an active request on it
	

public:
	virtual Node();
};