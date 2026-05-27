#include "node.hpp"
#include "../src/utils/global_state.hpp"
#include "node_manager.hpp"

void VoidNode::update(float deltaTime) {
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

	// for now, all void will do is consume a node every 3 seconds
	requests.pop();
	actionSwitch = false;
}

