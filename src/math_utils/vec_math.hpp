#pragma once
#include "SFML/Graphics.hpp"
#include <vector>

struct VecMath final {
    static inline float len(const sf::Vector2f& vec) {
        return std::sqrt(vec.x * vec.x + vec.y * vec.y);
    }

    static inline sf::Vector2f normalize(const sf::Vector2f& vec) {
        float vecLen = len(vec);
        return sf::Vector2f(vec.x / vecLen, vec.y / vecLen);
    }

    static inline sf::Vector2f inverse(const sf::Vector2f& vec) {
        return sf::Vector2f(
            -vec.x, -vec.y
        );
    }

    static inline sf::Vector2f matrixMultiply(const std::vector<sf::Vector2f>& matrixCols, const sf::Vector2f vectorToMultiplyWith) {
        float new_x = matrixCols[0].x * vectorToMultiplyWith.x + matrixCols[1].x * vectorToMultiplyWith.y;
        float new_y = matrixCols[0].y * vectorToMultiplyWith.x + matrixCols[1].y * vectorToMultiplyWith.y;
        return sf::Vector2f(new_x, new_y);
    }

    static inline sf::Vector2f applyRotation(float angle, sf::Vector2f vectorToRotate) {
        return matrixMultiply(buildRotationMatrix(angle), vectorToRotate);
    }

    static inline std::vector<sf::Vector2f> buildRotationMatrix(float rotation) {
        return std::vector<sf::Vector2f> {
            sf::Vector2f(cos(rotation), sin(rotation)),
            sf::Vector2f(-sin(rotation), cos(rotation))
        };
    }
};