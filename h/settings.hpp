#ifndef __SETTINGS_HPP__
#define __SETTINGS_HPP__

#include "SFML/Graphics.hpp"
#include <memory>

#include "definitions.hpp"

namespace VeX{

    class Settings{
    private:
        
    public:
        Settings();

        unsigned int screenWidth;
        unsigned int screenHeight;
        float gravity;
        unsigned int maxParticleCount;
        unsigned int currentParticleCount;
        sf::Vector2f defaultParticleMotionDampening;

        sf::Vector2f getScreenCenter();
    };

    using Settings_Ptr = std::unique_ptr<Settings>;

} // namespace VeX

#endif // __SETTINGS_HPP__
