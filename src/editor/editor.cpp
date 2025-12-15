
#include "editor.hpp"
#include "imgui.h"
#include "imgui-SFML.h"
#include "../generic_drawables/point.hpp"
#include "../math_utils/generic_math.hpp"
#include "../game/nodes/connective.hpp"
#include "../game/nodes/node_manager.hpp"

void renderImguiSfml(sf::RenderWindow& window, sf::Time& deltaTime) {
    ImGui::SFML::Update(window, deltaTime);
    ImGui::Begin("Window title");
    ImGui::Text("Window text!");
    ImGui::End();
}

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
    std::unique_ptr<NodeManager> nodeManager = std::make_unique<NodeManager>();

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
            }
        }

        // Update
        renderImguiSfml(window, deltaTime);

        // Clear window
        window.clear(sf::Color::Black);

        // Draw
        ImGui::SFML::Render(window);




        window.display();
    }
}