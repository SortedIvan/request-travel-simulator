#include "imgui.h"
#include "imgui-SFML.h"
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "editor/editor.hpp"

int main() {
	Editor editor(sf::Vector2i(1200, 1200), "Packet flow simulator");
	editor.initialize();
	editor.editorLoop();
	editor.~Editor();
	return EXIT_SUCCESS;
}