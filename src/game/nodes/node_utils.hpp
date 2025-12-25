#pragma once
#include "SFML/Graphics.hpp"

enum NodeType {
	NONE,
	PRODUCER,
	CONSUMER,
	DISTRIBUTOR,
	MULTIPLICATOR
};

static inline const char* nodeTypeToString(NodeType nt)
{
    switch (nt)
    {
		case NONE:       		return "None";
		case PRODUCER:   		return "P";
        case CONSUMER:   		return "C";
		case DISTRIBUTOR: 		return "D";
		case MULTIPLICATOR: 	return "M";
        default:                return "None";
    }
}

struct NodeCreateArgs {
	NodeType nodeType;
	int nodeShapeSize;
	sf::Vector2f position;
	sf::Color nodeColor;

	NodeCreateArgs(NodeType nodeType, int nodeShapeSize,
		const sf::Vector2f position, sf::Color nodeColor) {
		this->nodeType = nodeType;
		this->nodeShapeSize = nodeShapeSize;
		this->position = position;
		this->nodeColor = nodeColor;
	}
};
