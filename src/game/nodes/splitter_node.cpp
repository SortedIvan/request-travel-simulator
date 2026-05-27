#include "node.hpp"
#include "node_manager.hpp"
#include "../src/utils/global_state.hpp"


void SplitterNode::update(float deltaTime) {
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

	// splitter cant do anything without existing requests to process
	if (requests.empty()) {
		return;
	}

	std::size_t nodeConnectionsSize = getNodeConnections().size();
	auto& requestToSplit = requests.front();

	if (nodeConnectionsSize <= numberOfConnectionsToSplitTo) {
		
		for (int i = 0; i < nodeConnectionsSize; ++i) {
			nodeManager->addRequest(
				Request(requestToSplit.get()->getColor(), 10, 10,
					this->getNodeShape().getPosition(),
					nodeConnections[i].getNodeFromAndTo().second->getNodeShape().getPosition(),
					this->getId())
			);
		}
	}
	else {
		int splitConnectionsCounter = 0;

		while (splitConnectionsCounter < numberOfConnectionsToSplitTo) {
			if (splitterConnectionIndex >= nodeConnectionsSize) {
				splitterConnectionIndex = 0;
			}

			nodeManager->addRequest(
				Request(requestToSplit.get()->getColor(), 10, 10,
					this->getNodeShape().getPosition(),
					nodeConnections[splitterConnectionIndex].getNodeFromAndTo().second->getNodeShape().getPosition(),
					this->getId())
			);

			splitterConnectionIndex++;
			splitConnectionsCounter++;
		}
	}

	actionSwitch = false;
	requests.pop();
}

