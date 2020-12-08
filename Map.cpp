#include "Map.h"

Map::Map(int width, int height)
: mWidth (width)
, mHeight (height)
{
}

void Map::setWalkableAt(sf::Vector2i pos, bool a)
{
    if (pos.x < mWidth && pos.x >= 0 && pos.y < mHeight && pos.y >= 0)
        mWalkable[pos.x][pos.y] = a;
}

void Map::setPlaceableAt(sf::Vector2i pos, bool a)
{
    if (pos.x < mWidth && pos.x >= 0 && pos.y < mHeight && pos.y >= 0)
        mPlaceable[pos.x][pos.y] = a;
}

void Map::setWalkableAt(sf::Vector2i pos, sf::Vector2i size, bool a)
{
    if (pos.x < mWidth &&
        pos.x >= 0 &&
        pos.y < mHeight &&
        pos.y >= 0 &&
        pos.x + size.x <= mWidth &&
        pos.y + size.y <= mHeight) {

        for (int i = pos.x; i < pos.x + size.x; ++i) {
            for (int j = pos.y; j < pos.y + size.y; ++j) {
                mWalkable[i][j] = a;
            }
        }

    }
}

void Map::setPlaceableAt(sf::Vector2i pos, sf::Vector2i size, bool a)
{
    if (pos.x < mWidth &&
        pos.x >= 0 &&
        pos.y < mHeight &&
        pos.y >= 0 &&
        pos.x + size.x <= mWidth &&
        pos.y + size.y <= mHeight) {

        for (int i = pos.x; i < pos.x + size.x; ++i) {
            for (int j = pos.y; j < pos.y + size.y; ++j) {
                mPlaceable[i][j] = a;
            }
        }

    }
}

void Map::printWalkable()
{
    for (int i = 0; i < mHeight; ++i) {
        for (int j = 0; j < mWidth; ++j) {
            std::cout << isWalkableAt(sf::Vector2i(j, i));
        }
        std::cout << std::endl;
    }
}

void Map::printPlaceable()
{
    for (int i = 0; i < mHeight; ++i) {
        for (int j = 0; j < mWidth; ++j) {
            std::cout << isPlaceableAt(sf::Vector2i(j, i));
        }
        std::cout << std::endl;
    }
}

// modified version (Justin Heyes-Jones)
bool Map::isPathBetween(sf::Vector2i vectorStart, sf::Vector2i vectorEnd)
{
    AStarSearch<MapSearchNode> astarsearch;

    // Create a start state
    MapSearchNode nodeStart;
    nodeStart.x = vectorStart.x;
    nodeStart.y = vectorStart.y;

    // Define the goal state
    MapSearchNode nodeEnd;
    nodeEnd.x = vectorEnd.x;
    nodeEnd.y = vectorEnd.y;

    // Set Start and goal states
    astarsearch.SetStartAndGoalStates( nodeStart, nodeEnd );

    unsigned int SearchState;
    unsigned int SearchSteps = 0;

    do
    {
        SearchState = astarsearch.SearchStep(*this);
        SearchSteps++;
    }
    while( SearchState == AStarSearch<MapSearchNode>::SEARCH_STATE_SEARCHING );

    if( SearchState == AStarSearch<MapSearchNode>::SEARCH_STATE_SUCCEEDED )
    {
        MapSearchNode *node = astarsearch.GetSolutionStart();

        int steps = 0;

        for( ;; )
        {
            node = astarsearch.GetSolutionNext();

            if( !node )
            {
                break;
            }

            steps ++;

        };

        // Once you're done with the solution you can free the nodes up
        astarsearch.FreeSolutionNodes();
        astarsearch.EnsureMemoryFreed();

        return true;
    }

    astarsearch.EnsureMemoryFreed();

    return false;
}

// modified version (Justin Heyes-Jones)
bool Map::isPathBetween(sf::Vector2i vectorStart, sf::Vector2i vectorEnd, std::vector<sf::Vector2i>& change)
{
    AStarSearch<MapSearchNode> astarsearch;

    // Create a start state
    MapSearchNode nodeStart;
    nodeStart.x = vectorStart.x;
    nodeStart.y = vectorStart.y;

    // Define the goal state
    MapSearchNode nodeEnd;
    nodeEnd.x = vectorEnd.x;
    nodeEnd.y = vectorEnd.y;

    // Set Start and goal states
    astarsearch.SetStartAndGoalStates( nodeStart, nodeEnd );

    unsigned int SearchState;
    unsigned int SearchSteps = 0;

    do
    {
        SearchState = astarsearch.SearchStep(*this);
        SearchSteps++;
    }
    while( SearchState == AStarSearch<MapSearchNode>::SEARCH_STATE_SEARCHING );

    if( SearchState == AStarSearch<MapSearchNode>::SEARCH_STATE_SUCCEEDED )
    {
        change.push_back(vectorStart);

        MapSearchNode *node       = astarsearch.GetSolutionStart();
        int steps = 0;

        for( ;; )
        {
            node = astarsearch.GetSolutionNext();

            if( !node )
            {
                break;
            }

            change.push_back(sf::Vector2i(node->x, node->y));

            steps ++;
        };

        // Once you're done with the solution you can free the nodes up
        astarsearch.FreeSolutionNodes();
        astarsearch.EnsureMemoryFreed();

        return true;
    }

    astarsearch.EnsureMemoryFreed();

    return false;
}

bool Map::checkPath()
{
    for (size_t i = 0; i < mCheckpoints.size() - 1; ++i) {
        if (!isPathBetween(mCheckpoints[i].getCenter(), mCheckpoints[i+1].getCenter()))
            return false;
    }
    return true;
}

bool Map::updatePathGround()
{
    mPath.clear();

    std::vector<std::vector<sf::Vector2i>> paths;

    paths.resize(mCheckpoints.size() - 1);

    for (size_t i = 0; i < mCheckpoints.size() - 1; ++i) {
        if (!isPathBetween(mCheckpoints[i].getCenter(), mCheckpoints[i+1].getCenter(), paths[i]))
            return false;

        //std::vector<sf::Vector2i> temp = paths[i];
        sf::Vector2i tempv;

        for( std::vector<sf::Vector2i>::iterator check = paths[i].begin(), current = paths[i].begin() + 1; current != paths[i].end(); ) {
            if ( myn::walkable( (sf::Vector2f) *check, (sf::Vector2f) *current, *this ) ) {
                tempv = *current;
                current = paths[i].erase( current );
                //temp = paths[i];
            } else {
//
//                for (int j = std::distance(paths[i].begin(), check); j < std::distance(paths[i].begin(), current); ++j) {
//                    if ( myn::walkable( (sf::Vector2f) *current, (sf::Vector2f) temp[j] ) ) {
//                        paths[i][std::distance(paths[i].begin(), current)] = temp[j];
//                        break;
//                    }
//                    if (j >= std::distance(paths[i].begin(), check))
//                        paths[i][std::distance(paths[i].begin(), current)] = tempv;
//                }

                //paths[i][std::distance(paths[i].begin(), current)] = tempv;
                paths[i].insert(current, tempv);
                check = current++;
            }
        }

        mPath.insert( mPath.end(), paths[i].begin(), paths[i].end() );
    }

    mPath.push_back(mCheckpoints[mCheckpoints.size() - 1].getCenter());

    return true;
}

bool Map::updatePathAir()
{
    mPath.clear();

    for (size_t i = 0; i < mCheckpoints.size(); ++i) {
        mPath.push_back( mCheckpoints[i].getCenter() );
    }

    return true;
}

bool Map::isWalkableAt(sf::Vector2i pos)
{
    if (pos.x >= mWidth ||
        pos.x < 0 ||
        pos.y >= mHeight ||
        pos.y < 0 ||
        !mWalkable[pos.x][pos.y])
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool Map::isWalkableAt(sf::Vector2i pos, sf::Vector2i size)
{
    if (pos.x < mWidth &&
        pos.x >= 0 &&
        pos.y < mHeight &&
        pos.y >= 0 &&
        pos.x + size.x <= mWidth &&
        pos.y + size.y <= mHeight) {

        for (int i = pos.x; i < pos.x + size.x; ++i) {
            for (int j = pos.y; j < pos.y + size.y; ++j) {
                if (mWalkable[i][j] == false) {
                    return false;
                }
            }
        }

        return true;
    }
    return false;
}

bool Map::isPlaceableAt(sf::Vector2i pos)
{
    if (pos.x >= mWidth ||
        pos.x < 0 ||
        pos.y >= mHeight ||
        pos.y < 0 ||
        !mPlaceable[pos.x][pos.y])
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool Map::isPlaceableAt(sf::Vector2i pos, sf::Vector2i size)
{
    if (pos.x < mWidth &&
        pos.x >= 0 &&
        pos.y < mHeight &&
        pos.y >= 0 &&
        pos.x + size.x <= mWidth &&
        pos.y + size.y <= mHeight) {

        for (int i = pos.x; i < pos.x + size.x; ++i) {
            for (int j = pos.y; j < pos.y + size.y; ++j) {
                if (mPlaceable[i][j] == false) {
                    return false;
                }
            }
        }

        return true;
    }
    return false;
}

bool Map::createMap()
{
    if (mWidth > 1 &&
        mHeight > 1)
    {
            mWalkable.resize(mWidth);
            for (int i = 0; i < mWidth; ++i)
                mWalkable[i].resize(mHeight, true);
            mPlaceable.resize(mWidth);
            for (int i = 0; i < mWidth; ++i)
                mPlaceable[i].resize(mHeight, true);
            return true;
    }
    return false;
}


