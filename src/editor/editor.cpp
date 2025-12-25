#include "editor.hpp"
#include "imgui.h"
#include "imgui-SFML.h"
#include "../utils/logger.hpp"
#include "../utils/file_util.hpp"
#include "../generic_drawables/point.hpp"
#include "../math_utils/generic_math.hpp"
#include "../game/connectives/connective.hpp"
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

void Editor::initialize() {
    FileUtil::tryLoadFont(this->nodeLabelFont, PIXEL_FONT_PATH);
}

void Editor::editorLoop() 
{
    std::unique_ptr<NodeManager> nodeManager = std::make_unique<NodeManager>(nodeLabelFont);
    NodeType selectedNodeTypeToCreate = NodeType::PRODUCER;

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
                if (e.text.unicode >= '0' && e.text.unicode <= '9') {
                    const int digitValue = e.text.unicode - '0';
                    selectedNodeTypeToCreate = static_cast<NodeType>(digitValue);
                }
            }

            if (e.type == sf::Event::MouseButtonReleased && !io.WantCaptureMouse) {
                const int nodeId = nm->addNode(
                    selectedNodeTypeToCreate,
                    30.f,
                    (sf::Vector2f)sf::Mouse::getPosition(window),
                    sf::Color::White
                );

                Logger::info(__FILE__, __LINE__, "Nodes size: " + std::to_string(nm->getNodesView().size()));
            
                //addTransitionsToAllOtherNodesTest(nodeId, nm);
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