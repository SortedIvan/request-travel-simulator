#pragma once
#include "SFML/Graphics.hpp"

struct GeometryMath final {
    static inline bool checkCircleContainsPoint(float circleRadius, sf::Vector2f circleCenter, sf::Vector2f point) {
        float radiusSqrd = circleRadius * circleRadius;
        float lhsOfCircleEquation = std::pow((point.x - circleCenter.x), 2) + std::pow((point.y - circleCenter.y), 2);
        return radiusSqrd >= lhsOfCircleEquation; // its in the circle if >=
    }
};