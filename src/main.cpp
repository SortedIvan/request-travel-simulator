#include "SFML/Graphics.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 800), "Test application");
    sf::Event e;

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