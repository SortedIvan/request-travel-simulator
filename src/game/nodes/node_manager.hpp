#include <vector>
#include <stack>
#include "node.hpp"
#include "node_utils.hpp"

class NodeManager {
private:
	std::vector<std::unique_ptr<Node>> nodes;
	std::stack<int> idStack;
	sf::Color defaultConnectiveColor = sf::Color::White;
	sf::Color defaultNodeColor = sf::Color::White;
	sf::Color defaultNodeLabelFillColor = sf::Color::Black;
	sf::Font& nodeLabelFont;

	int nodeIdCounter = 0;

	bool checkIfIdValid(int id);
	bool checkIfConnectionExists(int nodeFrom, int nodeTo);
	int getNodeId();

	std::unique_ptr<Node> createNode(const NodeCreateArgs& nodeArgs);

public:
	NodeManager(sf::Font& nodeLabelFont);
	~NodeManager();
	
	Node* getNode(int nodeIndex);
	void connectTwoNodes(int nodeFrom, int nodeTo);
	void addNode(std::unique_ptr<Node> node);
	int addNode(const NodeCreateArgs& nodeCreateArgs);
	void removeNode(int id);
	void draw(sf::RenderWindow& window);
	void update(float deltaTime);
	const std::vector<std::unique_ptr<Node>>& getNodesView();
	std::vector<std::unique_ptr<Node>>& getNodesModifiable();
};