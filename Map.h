#ifndef MAP_H
#define MAP_H

#include <vector>
#include <iostream>
#include <memory>
#include <SFML/System/Vector2.hpp>

#include "stlastar.h"
#include "MapSearchNode.h"
#include "MyHelperFunctions.h"

#include "Checkpoint.h"

class Game;

class Map
{
public:
    Map(int, int);

    void setWalkableAt(sf::Vector2i, bool);
    void setPlaceableAt(sf::Vector2i, bool);

    void setWalkableAt(sf::Vector2i, sf::Vector2i, bool);
    void setPlaceableAt(sf::Vector2i, sf::Vector2i, bool);

    void printWalkable();
    void printPlaceable();
    bool isPathBetween(sf::Vector2i, sf::Vector2i);
    bool isPathBetween(sf::Vector2i, sf::Vector2i, std::vector<sf::Vector2i>& change);

    bool checkPath();
    bool updatePathGround();
    bool updatePathAir();

    int getWidth() const;
    int getHeight() const;
    bool isWalkableAt(sf::Vector2i pos);
    bool isWalkableAt(sf::Vector2i pos, sf::Vector2i s);
    bool isPlaceableAt(sf::Vector2i);
    bool isPlaceableAt(sf::Vector2i pos, sf::Vector2i s);

    std::vector<sf::Vector2i> getPath() const;

    std::vector<Checkpoint>& getCheckpoints();

private:
    int mWidth;
    int mHeight;
    std::vector<std::vector<bool>> mWalkable;
    std::vector<std::vector<bool>> mPlaceable;

    std::vector<sf::Vector2i> mPath;

    std::vector<Checkpoint> mCheckpoints;

public:
    bool createMap();

};

inline int Map::getWidth() const
{
    return mWidth;
}

inline int Map::getHeight() const
{
    return mHeight;
}

inline std::vector<sf::Vector2i> Map::getPath() const
{
    return mPath;
}

inline std::vector<Checkpoint>& Map::getCheckpoints()
{
    return mCheckpoints;
}


#endif
