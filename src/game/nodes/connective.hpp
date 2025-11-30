#include "node.hpp"
#include <vector>
#include "../src/generic_drawables/dashed_line.hpp"

class Connective {
private:
	bool active = true;
	int requestsPassedThrough = 0;
	float connectiveEndSideLength = 5.f;
	Node* nodeFrom;
	Node* nodeTo;
	DashedLine connectiveLine;
	sf::ConvexShape connectiveEnd;
	sf::Color connectiveColor;

	void initializeConnectiveDrawable();
public:
	~Connective();
	Connective(Node* nodeFrom, Node* nodeTo, const sf::Color connectiveColor);
	bool isActive();
	void setIsActive(const bool isActive);
	void draw(sf::RenderWindow& window);
	void move();
	void incrementRequestsPassedThrough();
	int getRequestsPassedThrough();
};