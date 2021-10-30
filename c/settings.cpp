#include "../h/settings.hpp"

namespace VeX{

    Settings::Settings():
        screenWidth(1280),
        screenHeight(720),
        gravity(Definition::gravitationalConstant),
        maxParticleCount(32'000),
        //maxParticleCount(2560*1440),
        currentParticleCount(0),
        defaultParticleMotionDampening(Definition::defaultParticleMotionDampening),
        backgroundColor(0,0,0),
        clearWindow(true),
        drawWindow(true)
    {
        //Config loading stuff soon™
    }

    sf::Vector2f Settings::getScreenCenter(){
        return sf::Vector2f(float(screenWidth)/2.f, float(screenHeight)/2.f);
    }

} // namespace VeX
