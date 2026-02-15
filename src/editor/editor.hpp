#include "SFML/Graphics.hpp"
#include <string>

enum EditorState {
	VIEW,
	ADDING_NODE,
	ADDING_CONNECTION,
	RUNNING_SIMULATION
};

class Editor {
private:
	sf::RenderWindow window;
	sf::Event e;
	sf::Clock deltaTimeClock;
	sf::Time deltaTime;

	// Fonts
	sf::Font nodeLabelFont;
	
	EditorState editorState = EditorState::VIEW;

	// Consts
	const std::string PIXEL_FONT_PATH = "testfont.ttf";

	void renderImguiSfml(sf::RenderWindow& window, sf::Time& deltaTime);

public:
	void editorLoop();
	void draw();
	void update();
	void initialize();

	void setState(EditorState editorState);
	EditorState getState();
	std::string editorStateToString(const EditorState& editorState);

	Editor(sf::Vector2i screenSize, std::string applicationName);
	~Editor();
};