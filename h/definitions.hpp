#ifndef __DEFINITIONS_HPP__
#define __DEFINITIONS_HPP__

#include <memory>
#include <map>
#include <string>
#include <SFML/Graphics.hpp>
#include "utilities.hpp"
#include "engine.hpp"

using TextureMap = std::map<std::string, std::string>;

namespace Definition {

    constexpr auto offScreenLimitMult = 100.f;

    constexpr auto defaultMaxParticleCount = 1000;
    const sf::Vector2f defaultParticleMotionDampening = {0.1,0.1};

    constexpr float gravitationalConstant = 9.80665 * 1.f;

    //Texture stuff
    std::string textureDirectory = "assets/textures/";
    TextureMap textures {
        {"defaultParticle", textureDirectory + "particle.png"},
        {"demoImage", textureDirectory + "VexedTea.png"}
    };
}

#endif // __DEFINITIONS_HPP__
