//#ifndef RESOURCEMANAGER_H
//#define RESOURCEMANAGER_H
//
//#include <iostream>
//
//#include <SFML/Graphics.hpp>
//#include <Thor/Animation.hpp>
//#include <Thor/Resources.hpp>
//#include <Thor/Particles.hpp>
//
//class ResourceManager
//{
//    public:
//        ResourceManager();
//
//        bool init();
//
//        sf::Texture rock,
//                    grass,
//                    tower_base,
//                    tower_crossbow,
//                    tower_arrow,
//                    grunt,
//                    hpbar;
//
//        thor::FrameAnimation grunt_walk,
//                                    tower_default,
//                                    tower_shoot;
//
//        thor::ColorGradient healthbar_color;
//};

//#endif

#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <iostream>

#include <SFML/Graphics.hpp>
#include <Thor/Animations.hpp>
#include <Thor/Resources.hpp>
#include <Thor/Particles.hpp>
#include <SFML/Audio/Music.hpp>

namespace ResourceManager
{
    bool init();

    extern sf::Texture rock,
                grass,
                tower_base,
                tower_crossbow,
                tower_arrow,
                grunt,
                hpbar;

    extern sf::Font font;

    extern thor::FrameAnimation grunt_walk,
                                tower_default,
                                tower_shoot;

    extern thor::ColorGradient healthbar_color;

    extern sf::Music music;
}

#endif
