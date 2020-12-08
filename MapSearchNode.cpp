////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// STL A* Search implementation
// (C)2001 Justin Heyes-Jones

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// modified version: removed useless stuff and added diagonal movement

#include "MapSearchNode.h"

bool IsFree( int x, int y, Map& m )
{
    if( x < 0 ||
        x >= (int) m.getWidth() ||
        y < 0 ||
        y >= (int) m.getHeight() ||
        !m.isWalkableAt(sf::Vector2i(x, y))
      )
    {
        return false;
    }

    return true;
}

bool MapSearchNode::IsSameState( MapSearchNode &rhs )
{
	// same state in a maze search is simply when (x,y) are the same
	if( (x == rhs.x) &&
		(y == rhs.y) )
	{
		return true;
	}
	else
	{
		return false;
	}
}

void MapSearchNode::PrintNodeInfo()
{
	char str[100];
	sprintf( str, "Node position : (%d,%d)\n", x,y );

	cout << str;
}

// Here's the heuristic function that estimates the distance from a Node
// to the Goal.

float MapSearchNode::GoalDistanceEstimate( MapSearchNode &nodeGoal )
{
	float xd = float( ( (float)x - (float)nodeGoal.x ) );
	float yd = float( ( (float)y - (float)nodeGoal.y) );

	return xd + yd;
}

bool MapSearchNode::IsGoal( MapSearchNode &nodeGoal )
{

	if( (x == nodeGoal.x) &&
		(y == nodeGoal.y) )
	{
		return true;
	}

	return false;
}

// This generates the successors to the given Node. It uses a helper function called
// AddSuccessor to give the successors to the AStar class. The A* specific initialisation
// is done for each node internally, so here you just set the state information that
// is specific to the application
bool MapSearchNode::GetSuccessors( AStarSearch<MapSearchNode> *astarsearch, MapSearchNode *parent_node, Map& m )
{

	int parent_x = -1;
	int parent_y = -1;

	if( parent_node )
	{
		parent_x = parent_node->x;
		parent_y = parent_node->y;
	}


	MapSearchNode NewNode;

    bool left=false, up=false, right=false, down=false;

	// push each possible move except allowing the search to go backwards

	if( IsFree( x-1, y, m )
        && !((parent_x == x-1) && (parent_y == y))
	  )
	{
		NewNode = MapSearchNode( x-1, y, false );
		astarsearch->AddSuccessor( NewNode );
        left = true;
	}

	if( IsFree( x, y-1, m )
		&& !((parent_x == x) && (parent_y == y-1))
	  )
	{
		NewNode = MapSearchNode( x, y-1, false );
		astarsearch->AddSuccessor( NewNode );
        up = true;
	}

	if( IsFree( x+1, y, m )
		&& !((parent_x == x+1) && (parent_y == y))
	  )
	{
		NewNode = MapSearchNode( x+1, y, false );
		astarsearch->AddSuccessor( NewNode );
        right = true;
	}

	if( IsFree( x, y+1, m )
		 && !((parent_x == x) && (parent_y == y+1))
		)
	{
		NewNode = MapSearchNode( x, y+1, false );
		astarsearch->AddSuccessor( NewNode );
        down = true;
	}

    //* allow diagonal as well

    if( left )
    {
        if( up   && IsFree( x-1, y-1, m )
            && !((parent_x == x-1) && (parent_y == y-1))
          )
        {
            NewNode = MapSearchNode( x-1, y-1, true );
            astarsearch->AddSuccessor( NewNode );
        }
        if( down && IsFree( x-1, y+1, m )
            && !((parent_x == x-1) && (parent_y == y+1))
          )
        {
            NewNode = MapSearchNode( x-1, y+1, true );
            astarsearch->AddSuccessor( NewNode );
        }
    }
    if( right )
    {
        if( up   && IsFree( x+1, y-1, m )
            && !((parent_x == x+1) && (parent_y == y-1))
          )
        {
            NewNode = MapSearchNode( x+1, y-1, true );
            astarsearch->AddSuccessor( NewNode );
        }
        if( down && IsFree( x+1, y+1, m )
            && !((parent_x == x+1) && (parent_y == y+1))
          )
        {
            NewNode = MapSearchNode( x+1, y+1, true );
            astarsearch->AddSuccessor( NewNode );
        }
    }

	return true;
}

// given this node, what does it cost to move to successor. In the case
// of our map the answer is the map terrain value at this node since that is
// conceptually where we're moving

float MapSearchNode::GetCost( MapSearchNode &successor )
{
	return successor.IsDiagonal() ? (float) sqrt(2) : 1.f;

}

bool MapSearchNode::IsDiagonal()
{
    return diagonal;
}
