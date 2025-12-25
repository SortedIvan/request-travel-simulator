#include <vector>
#include <stack>
#include "node.hpp"

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

public:
	NodeManager(sf::Font& nodeLabelFont);
	~NodeManager();
	
	void connectTwoNodes(int nodeFrom, int nodeTo);
	void addNode(std::unique_ptr<Node> node);
	int addNode(NodeType nodeType, int nodeShapeSize,
		const sf::Vector2f position, sf::Color nodeColor);
	void removeNode(int id);
	void draw(sf::RenderWindow& window);
	void update(float deltaTime);
	const std::vector<std::unique_ptr<Node>>& getNodesView();
	std::vector<std::unique_ptr<Node>>& getNodesModifiable();
};