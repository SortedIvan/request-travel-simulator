#include "node.hpp"
#include "../src/utils/global_state.hpp"


void SplitterNode::update(float deltaTime) {
	if (!GlobalState::getSimulationOn()) {
		return;
	}

	if (timeUntilAction <= 0) {
		timeUntilAction = rateOfActionMs;
		actionSwitch = true;
	}


}

