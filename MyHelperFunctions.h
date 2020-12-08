#ifndef MYHELPERFUNCTIONS_H
#define MYHELPERFUNCTIONS_H

#include <cmath>
#include <math.h>

#include <SFML/System/Vector2.hpp>
#include <Thor/Math.hpp>

#include "Map.h"

class Map;

namespace myn {

    float getAngleBetween(sf::Vector2f p1, sf::Vector2f p2);

    extern float EPSILON;

    bool isPointBetween(sf::Vector2f a, sf::Vector2f b, sf::Vector2f c);

    float getDistanceBetween(sf::Vector2f a, sf::Vector2f b);

    sf::Vector2i round(sf::Vector2f);

    bool walkable( sf::Vector2f pointA, sf::Vector2f pointB, Map& );

    sf::Vector2f normalizeVector(sf::Vector2f vec);

    std::string dbl2str(double d);

    bool is_number(const std::string& s);

    unsigned long stringToUnsignedLong(const std::string& s);

}

#endif
