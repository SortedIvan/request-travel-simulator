#include "node.hpp"
#include "../src/utils/global_state.hpp"
#include "node_manager.hpp"
#include "../src/math_utils/generic_math.hpp"

void ColorRandomizerNode::update(float deltaTime) {
	if (!GlobalState::getSimulationOn()) {
		return;
	}

	checkForRequestCollision();

	if (timeUntilAction <= 0) {
		timeUntilAction = rateOfActionMs;
		actionSwitch = true;
	}

	if (!actionSwitch) {
		timeUntilAction -= deltaTime;
		return;
	}

	if (requests.empty()) {
		return;
	}

	if (connectiveIndex >= nodeConnections.size()) {
		connectiveIndex = 0;
	}

	nodeManager->addRequest(
		Request(sf::Color(GenericMath::getRandomInt(0, 255), GenericMath::getRandomInt(0,255), GenericMath::getRandomInt(0, 255)), 10, 10,
			this->getNodeShape().getPosition(),
			nodeConnections[connectiveIndex].getNodeFromAndTo().second->getNodeShape().getPosition(),
			this->getId())
	);

	connectiveIndex++;
	requests.pop();
}