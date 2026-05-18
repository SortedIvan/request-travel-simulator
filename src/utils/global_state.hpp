#pragma once
struct GlobalState {
	static bool SIMULATION_ON;

	static bool getSimulationOn() {
		return SIMULATION_ON;
	}

	static void setSimulationOn(bool _SIMULATION_ON) {
		SIMULATION_ON = _SIMULATION_ON;
	}
};
