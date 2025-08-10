#include "editor.hpp"

Editor::Editor(sf::Vector2i screenSize, std::string applicationName) 
	: window(sf::VideoMode(screenSize.x, screenSize.y), applicationName) {

}

// Destructor
Editor::~Editor() {
	
}

void Editor::run() {
    while (window.isOpen())
    {

        while (window.pollEvent(e))
        {
            if (e.type == sf::Event::Closed)
            {
                window.close();
            }

            if (e.type == sf::Event::TextEntered)
            {

            }
        }

        // Clear the window
        window.clear(sf::Color::Black);

        // draw

        // display
        window.display();
    }
}