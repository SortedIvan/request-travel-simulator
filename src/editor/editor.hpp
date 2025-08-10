#include "SFML/Graphics.hpp"
#include <string>
/*
	* Top level object in the hierarchy 
	* Manages the window && manager classes
*/
class Editor {
private:
	sf::RenderWindow window;
	sf::Event e;
public:
	void run();
	Editor(sf::Vector2i screenSize, std::string applicationName);
	~Editor();
};