#ifndef __DEFINITIONS_HPP__
#define __DEFINITIONS_HPP__

#include <memory>
#include <map>
#include <string>
#include <SFML/Graphics.hpp>
#include "vector_operators.hpp"

using TextureMap = std::map<std::string, std::string>;

namespace Definition {

    constexpr auto screenWidth = 2560;
    constexpr auto screenHeight = 1440;

    constexpr float gravitationalConstant = 
                    9.80665 * 1000.f;

    //Texture stuff
    std::string textureDirectory = "assets/textures/";
    TextureMap textures {
        {"defaultParticle", textureDirectory + "particle.png"}
    };
}

#endif // __DEFINITIONS_HPP__
