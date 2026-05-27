#pragma once
#include "SFML/Graphics.hpp"

enum NodeType {
	NONE,
	PRODUCER,
	SPLITTER,
	MERGER,
	COLOR_RANDOMIZER,
	VOID
};

static inline const char* nodeTypeToString(NodeType& nt)
{
    switch (nt)
    {
		case NONE:       		return "NONE";
		case PRODUCER:   		return "PRODUCE";
		case SPLITTER: 			return "SPLIT";
		case MERGER:			return "MERGE";
		case COLOR_RANDOMIZER:  return "COLOR\nFLIP";
		case VOID:				return "VOID";
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
		case COLOR_RANDOMIZER:  return "COLOR\nFLIP";
		case VOID:				return "VOID";
		default:                return "NONE";
	}
}

struct NodeCreateArgs {
	NodeType nodeType;
	int nodeShapeSize;
	sf::Vector2f position;
	sf::Color nodeColor;
	sf::Font nodeFont;

	NodeCreateArgs(NodeType nodeType, int nodeShapeSize,
		const sf::Vector2f position, sf::Color nodeColor) {
		this->nodeType = nodeType;
		this->nodeShapeSize = nodeShapeSize;
		this->position = position;
		this->nodeColor = nodeColor;
	}
};
