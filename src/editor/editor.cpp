#include "editor.hpp"
#include "imgui.h"
#include "imgui-SFML.h"


Editor::Editor(sf::Vector2i screenSize, std::string applicationName) 
	: window(sf::VideoMode(screenSize.x, screenSize.y), applicationName) {
    ImGui::SFML::Init(window);

}

// Destructor
Editor::~Editor() {
	
}

void Editor::run() {
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

        // display
        window.display();
    }
}