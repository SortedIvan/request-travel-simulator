#pragma once
#include "SFML/Graphics.hpp"
#include "logger.hpp"

struct FileUtil final {
    static void tryLoadFont(sf::Font& font, std::string path)
    {
        if (!font.loadFromFile(path)) 
        {
            Logger::error(__FILE__, __LINE__, "Error loading file with path: " + path);
            system("pause");
        }
    }
};