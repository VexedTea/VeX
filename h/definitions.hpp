#ifndef __DEFINITIONS_HPP__
#define __DEFINITIONS_HPP__

#include <memory>
#include <map>
#include <string>
#include <cmath>
#include <SFML/Graphics.hpp>
#include "utilities.hpp"
//#include "engine.hpp"
#include "color_gradient.hpp"

using TextureMap = std::map<std::string, std::string>;

namespace Definition {

    constexpr auto offScreenLimitMult = 100.f;

    constexpr auto defaultMaxParticleCount = 1000;
    inline sf::Vector2f defaultParticleMotionDampening = {0.1,0.1};

    constexpr float gravitationalConstant = 9.80665 * 1.f;

    constexpr float G = 6.674*pow(10, -11);

    constexpr double pi = 3.14159265358979323846;

    inline VeX::Color_Gradient vexGradient({{102, 31, 196}, {21, 232, 255}, {255,255,255}});

    //Texture stuff
    inline std::string textureDirectory = "assets/textures/";
    inline TextureMap textures {
        {"defaultParticle", textureDirectory + "particle.png"},
        {"demoImage", textureDirectory + "VexedTea.png"}
    };
}

#endif // __DEFINITIONS_HPP__
