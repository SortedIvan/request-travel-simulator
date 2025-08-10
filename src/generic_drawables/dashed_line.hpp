#pragma once
#include <vector>

#include "../math_utils/vec_math.hpp"
#include "line.hpp"

class DashedLine {
private:
	std::vector<Line> lines;
	float linesLength;
	sf::Color lineColor;
public:
	void initializeLinesArray(sf::Vector2f pointA, sf::Vector2f pointB);
	DashedLine(sf::Vector2f pointA, sf::Vector2f pointB, float linesLength, sf::Color lineColor);
	DashedLine();
	void draw(sf::RenderWindow& window);
};