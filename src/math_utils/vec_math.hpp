#pragma once
#include "SFML/Graphics.hpp"

struct VecMath final {
    static inline float len(const sf::Vector2f& vec) {
        return std::sqrt(vec.x * vec.x + vec.y * vec.y);
    }

    static inline sf::Vector2f normalize(const sf::Vector2f& vec) {
        float vecLen = len(vec);
        return sf::Vector2f(vec.x / vecLen, vec.y / vecLen);
    }
};