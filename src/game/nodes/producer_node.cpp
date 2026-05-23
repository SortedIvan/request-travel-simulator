#include "node.hpp"
#include "node_manager.hpp"
#include "../src/utils/global_state.hpp"
#include "../src/utils/logger.hpp"
#include <algorithm>

void ProducerNode::update(float deltaTime) {
	checkForRequestCollision();
	if (!GlobalState::getSimulationOn()) { return; }

	if (nodeConnections.empty()) {
		if (!requests.empty()) {
			clearRequests(requests);
		}

		return;
	}

	if (timeUntilAction <= 0) {
		timeUntilAction = rateOfActionMs;
		actionSwitch = true;
	}

	if (actionSwitch) {
		if (connectiveIndex >= nodeConnections.size()) {
			connectiveIndex = 0;
		}

		nodeManager->addRequest(
			Request(sf::Color::Yellow, 10, 10,
				this->getNodeShape().getPosition(),
				nodeConnections[connectiveIndex].getNodeFromAndTo().second->getNodeShape().getPosition(),
				this->getId())
		);

		connectiveIndex++;
		actionSwitch = false;
	}

	timeUntilAction -= deltaTime;
	
	if (!requests.empty()) {
		clearRequests(requests);
	}
}