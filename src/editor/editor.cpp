#include "editor.hpp"
#include "imgui.h"
#include "imgui-SFML.h"
#include "../utils/logger.hpp"
#include "../generic_drawables/point.hpp"
#include "../math_utils/generic_math.hpp"
#include "../game/nodes/connective.hpp"
#include "../game/nodes/node_manager.hpp"

void renderImguiSfml(sf::RenderWindow& window, sf::Time& deltaTime);
void addTransitionsToAllOtherNodesTest(int newNodeId, NodeManager*& nodeManager);

Editor::Editor(sf::Vector2i screenSize, std::string applicationName) 
	: window(sf::VideoMode(screenSize.x, screenSize.y), applicationName) 
{
    ImGui::SFML::Init(window);
}

// Destructor
Editor::~Editor() 
{
	
}

void Editor::draw() {

}

void Editor::update() {

}

void Editor::run() 
{
    std::unique_ptr<NodeManager> nodeManager = std::make_unique<NodeManager>();

    while (window.isOpen())
    {
        deltaTime = deltaTimeClock.restart();
        NodeManager* nm = nodeManager.get();    
        const auto& io = ImGui::GetIO(); 

        while (window.pollEvent(e))
        {
            ImGui::SFML::ProcessEvent(e);

            if (e.type == sf::Event::Closed)
            {
                window.close();
            }

            if (e.type == sf::Event::TextEntered && !io.WantCaptureKeyboard)
            {

            }

            if (e.type == sf::Event::MouseButtonReleased && !io.WantCaptureMouse) {
                const int nodeId = nm->addNode(
                    NodeType::PRODUCER,
                    30.f,
                    (sf::Vector2f)sf::Mouse::getPosition(window),
                    sf::Color::White
                );

                Logger::info(__FILE__, __LINE__, "Nodes size: " + std::to_string(nm->getNodesView().size()));
            
                addTransitionsToAllOtherNodesTest(nodeId, nm);
            }
        }

        // Update
        renderImguiSfml(window, deltaTime);

        // Clear window
        window.clear(sf::Color::Black);

        // Draw everything else first
        nm->draw(window);
        
        // Finally, draw the UI (always ontop)
        ImGui::SFML::Render(window);

        window.display();
    }
}

void renderImguiSfml(sf::RenderWindow& window, sf::Time& deltaTime) {
    ImGui::SFML::Update(window, deltaTime);
    ImGui::Begin("Window title");
    ImGui::Text("Window text!");
    ImGui::End();
}

void addTransitionsToAllOtherNodesTest(int newNodeId, NodeManager*& nodeManager) {
    for (int i = 0; i < nodeManager->getNodesModifiable().size(); ++i) {
        auto& node = nodeManager->getNodesModifiable()[i];
        
        if (node->getId() == newNodeId) {
            continue;
        }

        nodeManager->connectTwoNodes(newNodeId, node->getId());
    }
}