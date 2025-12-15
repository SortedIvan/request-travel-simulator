#pragma once
#include <string>
#include <iostream>

struct Logger final {
	static void info(int loc = __LINE__, const std::string message = "Hello world") {
		std::cout << "[INFO][Line: " << loc << "]: " << message << std::endl;
	}

	constexpr static void error() {

	}

	constexpr static void warn() {

	}

};