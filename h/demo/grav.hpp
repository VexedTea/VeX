#ifndef __GRAV_HPP__
#define __GRAV_HPP__

#include <vector>
#include "../gravitational_system.hpp"
#include "../circle_object.hpp"

namespace VeX{
    enum class Mode{none, placing};

    class Grav : public State{
    private:
        Mode mode;
        Gravitational_System gravSystem;
        sf::Vector2f placingStartPoint;
    public:
        Grav();
        
        void init()override;
        
        void handleInput()override;
        
        void update(float delta)override;
        
        void draw(float delta)override;

        void stop()override;
    };

} // namespace VeX

#endif // __GRAV_HPP__
