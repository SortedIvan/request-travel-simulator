#include "dashed_line.hpp"

DashedLine::DashedLine(sf::Vector2f pointA, sf::Vector2f pointB, float linesLength, sf::Color lineColor) {
	this->linesLength = linesLength;
	this->lineColor = lineColor;
	
	initializeLinesArray(pointA, pointB);
}

void DashedLine::initializeLinesArray(sf::Vector2f pointA, sf::Vector2f pointB) {
	lines.clear();

	// 1) Calculate total distance and required number of dashes
	sf::Vector2f displacement = pointB - pointA;
	float displacementLen = VecMath::len(displacement);
	int numOfLines = displacementLen / linesLength;

	// 2) Get unit direction vector
	sf::Vector2f dirVec = VecMath::normalize(displacement);

	// 3) Determine final line segment position
	sf::Vector2f lastLinePoint = (linesLength * numOfLines * dirVec) + pointA;

	// 4) Compute correction vector
	sf::Vector2f differenceVec = pointB - lastLinePoint;

	// 5) Populate the dashed line segments
	for (int i = 0; i < numOfLines; ++i) {
		if (i % 2 == 0) { 
			sf::Vector2f subStartPoint = (dirVec * (float)i * linesLength) + pointA;
			sf::Vector2f subEndPoint = (dirVec * (float)(i + 1) * linesLength) + pointA;
			Line line(subStartPoint, subEndPoint, lineColor);
			lines.push_back(line);
		}
	}

	// 6) Adjust the last segment if necessary
	if (!lines.empty()) {
		lines.back().move(differenceVec);
	}
}

void DashedLine::draw(sf::RenderWindow& window) {
	for (int i = 0; i < lines.size(); ++i) {
		lines[i].draw(window);
	}
}

DashedLine::DashedLine() {

}