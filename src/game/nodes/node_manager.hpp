#include <vector>
#include <stack>
#include "node.hpp"

class NodeManager {
private:
	std::vector<Node*> nodes;
	std::stack<int> idStack;
	int nodeIdCounter = 0;
	sf::Color defaultConnectiveColor = sf::Color::White;
	sf::Color defaultNodeColor = sf::Color::White;
	
	bool checkIfIdValid(int id);
	bool checkIfConnectionExists(int nodeFrom, int nodeTo);
	int getNodeId();

public:
	NodeManager();
	~NodeManager();
	
	void connectTwoNodes(int nodeFrom, int nodeTo);
	void addNode(Node* node);
	int addNode(NodeType nodeType, int nodeShapeSize,
		const sf::Vector2f position, sf::Color nodeColor);
	void removeNode(int id);
	void draw(sf::RenderWindow& window);
	void update(float deltaTime);
	const std::vector<Node*>& getNodesView();
	std::vector<Node*>& getNodesModifiable();
};