#include "editor.hpp"
#include "../utils/logger.hpp"
#include "../utils/file_util.hpp"
#include "../utils/global_state.hpp"
#include "../generic_drawables/point.hpp"
#include "../math_utils/generic_math.hpp"
#include "imgui-SFML.h"

void addTransitionsToAllOtherNodesTest(int newNodeId, NodeManager*& nodeManager);
void addNewNode(NodeManager*& nm, const NodeType& selectedNodeTypeToCreate, sf::RenderWindow& window);
void selectNewNodeAndUnselectPrevious(const int& currentSelectedNode, int& previousSelectedNode, NodeManager*& nm);
bool checkIfNodeBeingSelected(int& selectedNode, const sf::Vector2f& mousePosition, NodeManager*& nodeManager);
void unselectNode(int& previousNode, NodeManager*& nm);
void resetDisplayConnective(Connective& connective);
void initializeDefaultEditorStateKeybinds(std::unordered_map<char, EditorState>& keybindMap);

Editor::Editor() {
    io = ImGui::GetIO();
}

Editor::Editor(sf::Vector2i screenSize, std::string applicationName) 
	: window(sf::VideoMode(screenSize.x, screenSize.y), applicationName) 
{
    ImGui::SFML::Init(window);
    window.setFramerateLimit(60);
}

// Destructor
Editor::~Editor() 
{
	
}

void Editor::draw() {

}

void Editor::initialize() {
    FileUtil::tryLoadFont(this->nodeLabelFont, PIXEL_FONT_PATH);
    initializeDefaultEditorStateKeybinds(this->stateKeybinds);
}

void Editor::handleInput(NodeManager* nm) {
    // ------------------ Mouse ------------------
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
    
    // ------------------ Keyboard + text ------------------
    if (e.type == sf::Event::TextEntered && !io.WantCaptureKeyboard) {
        changeState(e.text.unicode, nm);
    }

    if (e.text.unicode >= '0' && e.text.unicode <= '9') {
        const int digitValue = e.text.unicode - '0';
        selectedNodeTypeToCreate = static_cast<NodeType>(digitValue);
    }

    if (e.type == sf::Event::KeyReleased) {
        if (e.key.code == sf::Keyboard::LShift) {

        }
    }
}

void Editor::editorLoop() 
{
    resetDisplayConnective(editorDisplayConnective);
    
    while (window.isOpen())
    {
        deltaTime = deltaTimeClock.restart();
        NodeManager* nm = nodeManager.get();    
        this->io = ImGui::GetIO(); 

        while (window.pollEvent(e))
        {
            ImGui::SFML::ProcessEvent(window, e);
            
            if (e.type == sf::Event::Closed)
            {
                window.close();
            }

            handleInput(nm);

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

                        unselectNode(previousSelectedNode, nm);
                        unselectNode(currentSelectedNode, nm);
                        resetDisplayConnective(editorDisplayConnective);
                    }
                    else {
                        // Clicked on the same node or not on a node
                        resetDisplayConnective(editorDisplayConnective);
                    }
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
        nm->update(deltaTime.asMilliseconds());

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

void Editor::changeState(char stateChangeInput, NodeManager* nm) {
    const auto& stateKeybinds = getStateKeybinds();
    
    if (stateKeybinds.find(stateChangeInput) == stateKeybinds.end()) {
        // we are not attempting to change the state
        return;
    }

    const EditorState& newState = stateKeybinds.at(stateChangeInput);
    if (newState == editorState) { return; }
    
    // Do all clearouts here, for now just clear everything between state swaps for consistency
    unselectNode(currentSelectedNode, nm);
    resetDisplayConnective(editorDisplayConnective);
    currentSelectedNode = -1;

    setState(newState);

    if (newState == EditorState::RUNNING_SIMULATION) {
        if (GlobalState::getSimulationOn()) {
            Logger::info(__FILE__, __LINE__, "Turning simulation off");
            GlobalState::setSimulationOn(false);
        }
        else {
            Logger::info(__FILE__, __LINE__, "Turning simulation on");
            GlobalState::setSimulationOn(true);
        }
    }
}

void initializeDefaultEditorStateKeybinds(std::unordered_map<char, EditorState>& keybindMap) {
    keybindMap = {
        {'v', EditorState::VIEW},
        {'a', EditorState::ADDING_NODE},
        {'c', EditorState::ADDING_CONNECTION},
        {'r', EditorState::RUNNING_SIMULATION}
    };
}

void Editor::setState(EditorState editorState) {
    this->editorState = editorState;
}

EditorState Editor::getState() {
    return editorState;
}

// ----- IMGUI -------
void renderCurrentState(Editor& editor) {
    ImGui::Begin("Editor state");
    const std::string currentStateLabel = "Current editor state: " + editor.editorStateToString(editor.getState());
    ImGui::Text(currentStateLabel.c_str());
   
    if (editor.getState() == EditorState::ADDING_NODE) {
        std::string stateFullName = nodeTypeToStringFullName(editor.getSelectedNodeTypeToCreate());
        std::string labelAddingNode = "Current selected node type to add: " + stateFullName;
        ImGui::Text(labelAddingNode.c_str());
    }

    ImGui::Text("-------------------------------");
    ImGui::Text("Available keybinds");

    for (const auto& keybind : editor.getStateKeybinds()) {
        std::string keybindStr = std::string(1, static_cast<char>(std::toupper(keybind.first))) 
            + ": " + editor.editorStateToString(keybind.second);
        ImGui::Text(keybindStr.data());
    }

    ImGui::End();
}

const std::unordered_map<char, EditorState>& Editor::getStateKeybinds() {
    return this->stateKeybinds;
}

NodeType& Editor::getSelectedNodeTypeToCreate() {
    return this->selectedNodeTypeToCreate;
}

void Editor::renderImguiSfml(sf::RenderWindow& window, sf::Time& deltaTime) {
    ImGui::SFML::Update(window, deltaTime);
    renderCurrentState(*this);
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

void selectNewNodeAndUnselectPrevious(const int& currentSelectedNode, int& previousSelectedNode,
    NodeManager*& nm) {
    if (currentSelectedNode == -1) {
        return;
    }

    if (currentSelectedNode == previousSelectedNode) {
        return;
    }

    unselectNode(previousSelectedNode, nm);

    previousSelectedNode = -1;

    nm->getNodesModifiable()[currentSelectedNode]
        ->setIsSelected(true);
}

void unselectNode(int& previousNode, NodeManager*& nm) {
    if (previousNode != -1 && nm->getNodesModifiable()[previousNode]) {
        nm->getNodesModifiable()[previousNode]
            ->setIsSelected(false);
    }

    previousNode = -1;
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

