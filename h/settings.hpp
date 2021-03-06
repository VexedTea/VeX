#ifndef __SETTINGS_HPP__
#define __SETTINGS_HPP__

namespace VeX{

    class Settings{
    private:
        
    public:
        Settings():
            screenWidth(1280),
            screenHeight(720),
            gravity(Definition::gravitationalConstant),
            maxParticleCount(32'000),
            //maxParticleCount(2560*1440),
            currentParticleCount(0),
            defaultParticleMotionDampening(Definition::defaultParticleMotionDampening)
        {
            //Config loading stuff soon™
        }

        unsigned int screenWidth;
        unsigned int screenHeight;
        float gravity;
        unsigned int maxParticleCount;
        unsigned int currentParticleCount;
        sf::Vector2f defaultParticleMotionDampening;

        sf::Vector2f getScreenCenter(){
            return sf::Vector2f(float(screenWidth)/2.f, float(screenHeight)/2.f);
        }
    };

    using Settings_Ptr = std::unique_ptr<Settings>;

} // namespace VeX

#endif // __SETTINGS_HPP__
