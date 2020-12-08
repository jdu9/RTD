#include "MyHelperFunctions.h"

namespace myn {

    float getAngleBetween(sf::Vector2f p1, sf::Vector2f p2)
    {
            return std::atan2(p2.y - p1.y, p2.x - p1.x) * 180 / thor::Pi;
    }

    float EPSILON = 0.001f;

    bool isPointBetween(sf::Vector2f a, sf::Vector2f b, sf::Vector2f c)
    {
            float crossproduct = (c.y - a.y) * (b.x - a.x) - (c.x - a.x) * (b.y - a.y);
            if (std::abs(crossproduct) > EPSILON) return false;

            float dotproduct = (c.x - a.x) * (b.x - a.x) + (c.y - a.y)*(b.y - a.y);
            if (dotproduct < 0) return false;

            float squaredlengthba = (b.x - a.x)*(b.x - a.x) + (b.y - a.y)*(b.y - a.y);
            if (dotproduct > squaredlengthba) return false;

            return true;
    }

    float getDistanceBetween(sf::Vector2f a, sf::Vector2f b)
    {
        return std::sqrt(std::pow(b.y - a.y, 2) + std::pow(b.x - a.x, 2));
    }

    sf::Vector2f normalizeVector(sf::Vector2f vec) {
        float length = std::sqrt(vec.x * vec.x + vec.y * vec.y);
        return sf::Vector2f(vec.x / length, vec.y / length);
    }

    sf::Vector2i round(sf::Vector2f a)
    {
        return sf::Vector2i( (int) ( a.x + 0.5f ), (int) ( a.y + 0.5f ) );
    }

    bool walkable( sf::Vector2f pointA, sf::Vector2f pointB, Map& m )
    {
        sf::Vector2f vec_dir = pointB - pointA;

        float length = std::sqrt( vec_dir.x * vec_dir.x + vec_dir.y * vec_dir.y );

        vec_dir = sf::Vector2f( vec_dir.x / length, vec_dir.y / length );

//        float angle = myn::getAngleBetween( pointA, pointB );
//        float angle_left  =  ((angle + 90)/180)*thor::Pi;
//        float angle_right =  ((angle - 90)/180)*thor::Pi;

        int count = (int) ( length * 10.0f + 0.5f);

        sf::Vector2f temp = pointA + sf::Vector2f(0.5f, 0.5f);

        for( int i = 0; i < count; ++i)
        {
           temp += vec_dir * 0.1f;

           if( !(m.isWalkableAt( (sf::Vector2i) ( temp ) ) &&
                 m.isWalkableAt( (sf::Vector2i) ( temp + sf::Vector2f(+0.15f, +0.15f) ) ) &&
                 m.isWalkableAt( (sf::Vector2i) ( temp + sf::Vector2f(-0.15f, -0.15f) ) ) &&
                 m.isWalkableAt( (sf::Vector2i) ( temp + sf::Vector2f(-0.15f, +0.15f) ) ) &&
                 m.isWalkableAt( (sf::Vector2i) ( temp + sf::Vector2f(+0.15f, -0.15f) ) )
                 ) )
           {
                return false;
           }
        }

        return true;
    }

    // https://stackoverflow.com/questions/15165502/double-to-string-without-scientific-notation-or-trailing-zeros-efficiently
    std::string dbl2str(double d)
    {
        size_t len = std::snprintf(0, 0, "%.10f", d);
        std::string s(len+1, 0);
        // technically non-portable, see below
        std::snprintf(&s[0], len+1, "%.10f", d);
        // remove nul terminator
        s.pop_back();
        // remove trailing zeros
        s.erase(s.find_last_not_of('0') + 1, std::string::npos);
        // remove trailing point
        if(s.back() == '.') {
            s.pop_back();
        }
        return s;
    }

    unsigned long stringToUnsignedLong(const std::string& s)
    {
        unsigned long ulong;

        for (const char& c : s)
        {
            ulong += (int) c;
        }

        return ulong;
    }

    bool is_number(const std::string& s)
    {
        return !s.empty() && std::find_if(s.begin(), s.end(), [](char c) { return !std::isdigit(c); }) == s.end();
    }

}
