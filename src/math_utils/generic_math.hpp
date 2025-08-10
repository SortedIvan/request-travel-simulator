#pragma once
#include <random>
#include <algorithm>
#include "SFML/Graphics.hpp"

struct GenericMath final {
    // Shared RNG for all functions
    static inline std::mt19937& getRNG() {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        return gen;
    }

    static inline float getRandomFloat(float min, float max) {
        if (min > max) std::swap(min, max);
        std::uniform_real_distribution<float> dist(min, max);
        return dist(getRNG());
    }

    static inline int getRandomInt(int min, int max) {
        if (min > max) std::swap(min, max);
        std::uniform_int_distribution<int> dist(min, max);
        return dist(getRNG());
    }

    static inline sf::Vector2f getRandPointInRectangle(sf::Vector2f TL, sf::Vector2f BR) {
        float minX = std::min(TL.x, BR.x);
        float maxX = std::max(TL.x, BR.x);
        float minY = std::min(TL.y, BR.y);
        float maxY = std::max(TL.y, BR.y);

        std::uniform_real_distribution<float> distX(minX, maxX);
        std::uniform_real_distribution<float> distY(minY, maxY);

        return sf::Vector2f(
            distX(getRNG()),
            distY(getRNG())
        );
    }
};
