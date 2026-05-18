#include "node.hpp"
#include "node_manager.hpp"
#include "../src/utils/global_state.hpp"
#include "../src/utils/logger.hpp"

void ProducerNode::update(float deltaTime) {

	checkForRequestCollision();

	if (!GlobalState::getSimulationOn()) {
		return;
	}

	if (nodeConnections.empty()) {
		if (!requests.empty()) {
			requests.clear();
		}

		return;
	}


	if (timeUntilProduction <= 0) {
		timeUntilProduction = rateOfProductionMs;
		produceSwitch = true;
	}

	if (produceSwitch) {
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
		produceSwitch = false;
	}

	timeUntilProduction -= deltaTime;
	std::cout << timeUntilProduction << std::endl;
	
	if (!requests.empty()) {
		requests.clear();
	}
}

void ProducerNode::executeNodeBehavior(float deltaTime) {}