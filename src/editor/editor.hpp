#include "SFML/Graphics.hpp"
#include <string>
class Editor {
private:
	sf::RenderWindow window;
	sf::Event e;
	sf::Clock deltaTimeClock;
	sf::Time deltaTime;

	// Consts
	const std::string PIXEL_FONT_PATH = "testfont.ttf";

	// Fonts
	sf::Font nodeLabelFont;
public:
	void editorLoop();
	void draw();
	void update();
	void initialize();

	Editor(sf::Vector2i screenSize, std::string applicationName);
	~Editor();
};