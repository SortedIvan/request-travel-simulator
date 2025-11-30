#include "editor.hpp"
#include "imgui.h"
#include "imgui-SFML.h"
#include "../generic_drawables/point.hpp"
#include "../math_utils/generic_math.hpp"
#include "../game/nodes/connective.hpp"


Editor::Editor(sf::Vector2i screenSize, std::string applicationName) 
	: window(sf::VideoMode(screenSize.x, screenSize.y), applicationName) 
{
    ImGui::SFML::Init(window);
}

// Destructor
Editor::~Editor() 
{
	
}

void Editor::run() 
{
    std::vector<Connective> connectives;
    sf::Vector2f from;
    sf::Vector2f to;
    bool clicked = false;

    while (window.isOpen())
    {
        deltaTime = deltaTimeClock.restart();

        while (window.pollEvent(e))
        {
            ImGui::SFML::ProcessEvent(e);
            if (e.type == sf::Event::Closed)
            {
                window.close();
            }

            if (e.type == sf::Event::TextEntered)
            {

            }

            if (e.type == sf::Event::MouseButtonReleased) {
                if (clicked) {
                    to = (sf::Vector2f)sf::Mouse::getPosition(window);
                    connectives.emplace_back(from, to, sf::Color::Yellow);
                    clicked = false;
                }
                else {
                    from = (sf::Vector2f)sf::Mouse::getPosition(window);
                    clicked = true;
                }   
            }
        }

        // UPDATE
        ImGui::SFML::Update(window, deltaTime);

        ImGui::Begin("Window title");
        ImGui::Text("Window text!");

        ImGui::End();

        // Clear the window
        window.clear(sf::Color::Black);

        // draw
        ImGui::SFML::Render(window);

        for (int i = 0; i < connectives.size(); ++i) {
            connectives[i].draw(window);
        }

        // display
        window.display();
    }
}