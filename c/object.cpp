#include "../h/object.hpp"

namespace VeX{

    Object::Object(const sf::Vector2f & position, const sf::Vector2f & size, const sf::Vector2f & velocity, float mass, const sf::Vector2f & motionDampening):
        position(position),
        size(size),
        velocity(velocity),
        mass(mass),
        motionDampening(motionDampening),
        paused(false),
        hidden(false),
        previousPosition(position)
    {}

    Object::Object(const sf::Vector2f & position, const sf::Vector2f & velocity, float mass, const sf::Vector2f & motionDampening):
        Object(position, {0.f,0.f}, velocity, mass, motionDampening)
    {}

    Object::Object(const sf::Vector2f & position):
        Object(position, {0,0}, 0.f, {0,0})
    {}

    Object::Object(const sf::Vector2f & position, const sf::Vector2f & velocity):
        Object(position, velocity, 0.f, {0,0})
    {}

    Object::Object(const sf::Vector2f & position, float mass):
        Object(position, {0,0}, mass, {0,0})
    {}

    void Object::update(float delta){
        if(!paused){
            velocity = velocity / ((motionDampening * delta)+1);
            previousPosition = position;
            position += velocity * delta;
        }
    }

    void Object::draw(float){}

    void Object::gravTo(const sf::Vector2f & targetPos, float delta){
        if(!paused){
            if(targetPos == position){return;}
            float magnitude = sqrt(pow(targetPos.x - position.x, 2) + pow(targetPos.y - position.y, 2));
            sf::Vector2f direction = (targetPos - position)/magnitude;
            float v = -0.4*magnitude + (engine->settings->gravity * delta * pow(magnitude, 1.2)) + 3;
            velocity += direction * v;
        }
    }

    void Object::launchTo(const sf::Vector2f & targetPos){
        float distance = sqrt(pow(targetPos.x - position.x, 2) + pow(targetPos.y - position.y, 2));
        sf::Vector2f direction = (targetPos - position)/distance;
        float v = distance * motionDampening.x; //Change this
        velocity += (direction * v);
    }

    void Object::setPosition(const sf::Vector2f & newPos){
        previousPosition = position;
        position = newPos;
    }

    void Object::setPosition(const sf::Vector2i & newPos){
        setPosition(sf::Vector2f{static_cast<float>(newPos.x), static_cast<float>(newPos.y)});
    }

    sf::Vector2f Object::getPosition(){
        return position;
    }

    void Object::move(const sf::Vector2f & move){
        previousPosition = position;
        position += move;
    }

    void Object::setVelocity(const sf::Vector2f & newVel){
        velocity = newVel;
    }

    void Object::addVelocity(const sf::Vector2f & velAdd){
        velocity += velAdd;
    }

    sf::Vector2f Object::getVelocity(){
        return velocity;
    }

    float Object::getMass(){
        return mass;
    }

    void Object::addMass(float massAdd){
        mass += massAdd;
    }
    
    void Object::pause(){
        paused = true;
    }

    void Object::unpause(){
        paused = false;
    }

    void Object::hide(){
        hidden = true;
    }

    void Object::unhide(){
        hidden = false;
    }

    bool Object::isAt(const sf::Vector2f & targetPos, float range){
        return range > sqrt(pow(targetPos.x - position.x, 2) + pow(targetPos.y - position.y, 2));
    }

    void Object::goBack(){
        position = previousPosition;
    }

} // namespace VeX
