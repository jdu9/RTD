////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// STL A* Search implementation
// (C)2001 Justin Heyes-Jones

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// modified version: removed useless stuff and added diagonal movement

#ifndef MAPSEARCHNODE_H
#define MAPSEARCHNODE_H

#include "stlastar.h" // See header for copyright and usage information
#include "SFML/System/Vector2.hpp"

#include <iostream>
#include <stdio.h>
#include <math.h>
#include "Map.h"

class Map;

class MapSearchNode
{
public:
	int x;	 // the (x,y) positions of the node
	int y;
    bool diagonal;

	MapSearchNode() { x = y = 0; diagonal = false; }
	MapSearchNode( int px, int py, bool dg ) { x=px; y=py; diagonal=dg; }

	float GoalDistanceEstimate( MapSearchNode &nodeGoal );
	bool IsGoal( MapSearchNode &nodeGoal );
    bool GetSuccessors( AStarSearch<MapSearchNode> *astarsearch, MapSearchNode *parent_node, Map& m );
	float GetCost( MapSearchNode &successor );
	bool IsSameState( MapSearchNode &rhs );
    bool IsDiagonal();

	void PrintNodeInfo();
};

#endif
