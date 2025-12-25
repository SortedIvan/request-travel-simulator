#pragma once
#include <string>
#include <iostream>

// To do: this could cache files, etc.
// example, can have a map of raw __FILE__ to the parsed file
struct Logger final {
	static std::string getFileName(const std::string& file) {
		if (file.empty()) {
			return "none";
		}
		
		std::string fileName;

		for (int i = file.size() - 1; i >= 0; --i) {
			if (file[i] == '//') {
				break;
			}

			fileName = file[i] + fileName;
		}

		return fileName;
	}

	static void info(const std::string file = __FILE__, int loc = __LINE__, const std::string message = "Hello world") {
		std::cout << "[INFO][" << loc << "][" << getFileName(file) << "]" << message << std::endl;
	}

	static void error(const std::string file = __FILE__, int loc = __LINE__, const std::string message = "Hello world") {
		std::cout << "[ERROR][" << loc << "][" << getFileName(file) << "]" << message << std::endl;
	}

	static void warn(const std::string file = __FILE__, int loc = __LINE__, const std::string message = "Hello world") {
		std::cout << "[WARN][" << loc << "][" << getFileName(file) << "]" << message << std::endl;
	}
};