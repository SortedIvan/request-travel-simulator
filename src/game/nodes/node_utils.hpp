#pragma once
#include "SFML/Graphics.hpp"

enum NodeType {
	NONE,
	PRODUCER,
	SPLITTER,
	MERGER
};

static inline const char* nodeTypeToString(NodeType& nt)
{
    switch (nt)
    {
		case NONE:       		return "NONE";
		case PRODUCER:   		return "P";
		case SPLITTER: 			return "S";
		case MERGER:			return "M";
        default:                return "NONE";
    }
}

static inline const char* nodeTypeToStringFullName(NodeType& nt) {
	switch (nt)
	{
		case NONE:       		return "NONE";
		case PRODUCER:   		return "PRODUCER";
		case SPLITTER: 			return "SPLITTER";
		case MERGER: 			return "MERGER";
		default:                return "NONE";
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
