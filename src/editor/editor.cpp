#include "editor.hpp"
#include "imgui.h"
#include "imgui-SFML.h"
#include "../utils/logger.hpp"
#include "../utils/file_util.hpp"
#include "../generic_drawables/point.hpp"
#include "../math_utils/generic_math.hpp"
#include "../game/connectives/connective.hpp"
#include "../game/nodes/node_manager.hpp"

void addTransitionsToAllOtherNodesTest(int newNodeId, NodeManager*& nodeManager);
void addNewNode(NodeManager*& nm, const NodeType& selectedNodeTypeToCreate, sf::RenderWindow& window);
void selectNewNodeAndUnselectPrevious(const int& currentSelectedNode, const int& previousSelectedNode, NodeManager*& nm);
bool checkIfNodeBeingSelected(int& selectedNode, const sf::Vector2f& mousePosition, NodeManager*& nodeManager);
void unselectNode(const int& previousNode, NodeManager*& nm);
void resetDisplayConnective(Connective& connective);

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
    int currentSelectedNode = -1;
    Connective editorDisplayConnective;
    resetDisplayConnective(editorDisplayConnective);
    
    while (window.isOpen())
    {
        deltaTime = deltaTimeClock.restart();
        NodeManager* nm = nodeManager.get();    
        const auto& io = ImGui::GetIO(); 

        while (window.pollEvent(e))
        {
            ImGui::SFML::ProcessEvent(window, e);
            
            if (e.type == sf::Event::Closed)
            {
                window.close();
            }

            if (e.type == sf::Event::MouseMoved) {
                if (getState() == ADDING_CONNECTION && currentSelectedNode != -1) {
                        Node* currentNode = nm->getNode(currentSelectedNode);

                        if (currentNode) {
                            editorDisplayConnective.initializeConnectiveDrawableDummy(
                                currentNode->getNodeShape().getPosition(),
                                static_cast<sf::Vector2f>(sf::Mouse::getPosition(window))
                            );
                        }
                        else {
                            currentSelectedNode = -1;
                        }
                }

            }

            if (e.type == sf::Event::KeyReleased) {
                if (e.key.code == sf::Keyboard::LShift) {

                }
            }

            if (e.type == sf::Event::TextEntered && !io.WantCaptureKeyboard)
            {
                if (e.text.unicode == 'a') {
                    unselectNode(currentSelectedNode, nm);
                    currentSelectedNode = -1;
                    setState(EditorState::ADDING_NODE);
                    resetDisplayConnective(editorDisplayConnective);
                }
                else if (e.text.unicode == 'c') {
                    setState(EditorState::ADDING_CONNECTION);
                    resetDisplayConnective(editorDisplayConnective);

                    if (currentSelectedNode != -1) {
                        Node* currentNode = nm->getNode(currentSelectedNode);

                        if (currentNode) {
                            editorDisplayConnective.initializeConnectiveDrawableDummy(
                                currentNode->getNodeShape().getPosition(),
                                static_cast<sf::Vector2f>(sf::Mouse::getPosition(window))
                            );
                        }
                        else {
                            // Somehow the node got deleted, this not expected behavior but handling it gracefully
                            currentSelectedNode = -1;
                        }
                    }
                }
                else if (e.text.unicode == 's') {
                    // start the simulation

                }
                else if (e.text.unicode >= '0' && e.text.unicode <= '9') {
                    const int digitValue = e.text.unicode - '0';
                    selectedNodeTypeToCreate = static_cast<NodeType>(digitValue);
                }
            }

            if (e.type == sf::Event::MouseButtonReleased && !io.WantCaptureMouse) {
                // Capture previous selection JUST before it may change
                int previousSelectedNode = currentSelectedNode;

                bool nodeSelected = checkIfNodeBeingSelected(
                    currentSelectedNode,
                    static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)),
                    nm
                );

                if (!nodeSelected && getState() == EditorState::ADDING_NODE) {
                    addNewNode(nm, selectedNodeTypeToCreate, window);
                    unselectNode(previousSelectedNode, nm);
                    resetDisplayConnective(editorDisplayConnective);
                }
                else if (getState() == EditorState::ADDING_CONNECTION) {

                    if (currentSelectedNode != previousSelectedNode &&
                        currentSelectedNode != -1 &&
                        previousSelectedNode != -1)
                    {
                        nm->connectTwoNodes(previousSelectedNode, currentSelectedNode);
                        setState(EditorState::VIEW);
                    }

                    unselectNode(previousSelectedNode, nm);
                    unselectNode(currentSelectedNode, nm);
                }
                else {
                    selectNewNodeAndUnselectPrevious(
                        currentSelectedNode,
                        previousSelectedNode,
                        nm
                    );
                }
            }
        }

        // Update
        renderImguiSfml(window, deltaTime);

        // Clear window
        window.clear(sf::Color::Black);

        // Draw everything else first
        nm->draw(window);

        if (getState() == ADDING_CONNECTION) {
            editorDisplayConnective.draw(window);
        }

        // Finally, draw the UI (always ontop)
        ImGui::SFML::Render(window);

        window.display();
    }
}

void Editor::setState(EditorState editorState) {
    this->editorState = editorState;
}

EditorState Editor::getState() {
    return editorState;
}

void Editor::renderImguiSfml(sf::RenderWindow& window, sf::Time& deltaTime) {
    ImGui::SFML::Update(window, deltaTime);
    ImGui::Begin("Info");
    const std::string currentStateLabel = "Editor state: " + editorStateToString(getState());
    ImGui::Text(currentStateLabel.c_str());
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

void addNewNode(NodeManager*& nm, const NodeType& selectedNodeTypeToCreate, sf::RenderWindow& window) {
    NodeCreateArgs nodeCreateArgs = NodeCreateArgs(
        selectedNodeTypeToCreate,
        30.f,
        (sf::Vector2f)sf::Mouse::getPosition(window),
        sf::Color::White
    );
    
    const int nodeId = nm->addNode(nodeCreateArgs);

    Logger::info(__FILE__, __LINE__, "Nodes size: " + std::to_string(nm->getNodesView().size()));
            
    //addTransitionsToAllOtherNodesTest(nodeId, nm);
}

// To do: this can be improved massively by using a simple grid system
bool checkIfNodeBeingSelected(int& selectedNode, const sf::Vector2f& mousePosition, NodeManager*& nodeManager) {
    for (int i = 0; i < nodeManager->getNodesModifiable().size(); ++i) {
        const auto& node = nodeManager->getNodesModifiable()[i].get();
        const auto& nodeShape = node->getNodeShape().getCircleShape();
        
        // use our own point check as SFML uses a minimum bounding rectangle
        if (GenericMath::checkIfCircleContainsPoint(mousePosition, nodeShape.getPosition(), nodeShape.getRadius())) {
            selectedNode = node->getId();
            return true;
        }
    }

    selectedNode = -1;
    return false;
}

void selectNewNodeAndUnselectPrevious(const int& currentSelectedNode, const int& previousSelectedNode,
    NodeManager*& nm) {
    if (currentSelectedNode == -1) {
        return;
    }

    if (currentSelectedNode == previousSelectedNode) {
        return;
    }

    unselectNode(previousSelectedNode, nm);

    nm->getNodesModifiable()[currentSelectedNode]
        ->setIsSelected(true);
}

void unselectNode(const int& previousNode, NodeManager*& nm) {
    if (previousNode != -1 && nm->getNodesModifiable()[previousNode]) {
        nm->getNodesModifiable()[previousNode]
            ->setIsSelected(false);
    }
}

void resetDisplayConnective(Connective& connective) {
    connective = Connective();
    connective.setConnectiveColor(sf::Color::White);
}

std::string Editor::editorStateToString(const EditorState& editorState) {
    switch (editorState) {
        case VIEW:
            return "VIEW";
        case ADDING_NODE:
            return "ADDING_NODE";
        case ADDING_CONNECTION:
            return "ADDING_CONNECTION";
        case RUNNING_SIMULATION:
            return "RUNNING_SIMULATION";
        _:
        return "NONE";
    }
}
