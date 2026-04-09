#pragma once
#include "SFML/Graphics.hpp"
#include "imgui.h"
#include <string>
#include <unordered_map>
#include "../game/connectives/connective.hpp"
#include "../game/nodes/node_manager.hpp"


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
	sf::Font nodeLabelFont;
	EditorState editorState = EditorState::VIEW;
	std::unordered_map<char, EditorState> stateKeybinds;
	ImGuiIO io;
	std::unique_ptr<NodeManager> nodeManager = std::make_unique<NodeManager>(nodeLabelFont);
	NodeType selectedNodeTypeToCreate = NodeType::PRODUCER;
	int currentSelectedNode = -1;
	Connective editorDisplayConnective;

	const std::string PIXEL_FONT_PATH = "testfont.ttf";

	void renderImguiSfml(sf::RenderWindow& window, sf::Time& deltaTime);
	void handleInput(NodeManager* nm);
	void changeState(char stateChangeInput, NodeManager* nm);

public:
	void editorLoop();
	void draw();
	void initialize();

	const std::unordered_map<char, EditorState>& getStateKeybinds();
	NodeType& getSelectedNodeTypeToCreate();
	
	void setState(EditorState editorState);	
	EditorState getState();
	std::string editorStateToString(const EditorState& editorState);

	Editor();
	Editor(sf::Vector2i screenSize, std::string applicationName);
	~Editor();
};