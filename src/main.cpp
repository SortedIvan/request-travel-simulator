#include "imgui.h"
#include "imgui-SFML.h"

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"

#include "editor/editor.hpp"

int main() {
	Editor editor(sf::Vector2i(1000, 1000), "Packet flow simulator");
	editor.run();
	editor.~Editor();
	return EXIT_SUCCESS;
}
