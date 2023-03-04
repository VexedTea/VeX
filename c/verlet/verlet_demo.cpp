#include "../../h/verlet/verlet_demo.hpp"

namespace VeX{
    static sf::Color getRainbow(float t)
    {
        const float r = sin(t);
        const float g = sin(t + 0.33f * 2.0f * Definition::pi);
        const float b = sin(t + 0.66f * 2.0f * Definition::pi);
        return {static_cast<uint8_t>(255.0f * r * r),
                static_cast<uint8_t>(255.0f * g * g),
                static_cast<uint8_t>(255.0f * b * b)};
    }

    void Verlet_Demo::init(){
        solver.setConstraint(engine->settings->getScreenCenter(), min(engine->settings->getScreenCenter()));
        solver.setSubStepCount(8);
        solver.setSimulationUpdateRate(60.f);

        objectSpawnDelay = 0.025f;
        objectSpawnSpeed = 1200.0f * 1.f;
        objectSpawnPosition = engine->settings->getScreenCenter();
        objectSpawnPosition.y = objectSpawnPosition.y/50.f;
        objectMinRadius = 1.0f;
        objectMaxRadius = 20.0f;
        maxObjectCount = 1500;
        maxAngle = 0.1f;

        clock.restart();
    }

    void Verlet_Demo::update(float /*delta*/){
        if(solver.getObjectCount() < maxObjectCount && clock.getElapsedTime().asSeconds() >= objectSpawnDelay){
            clock.restart();
            auto& object = solver.addObject(objectSpawnPosition, 5.f);
            const float time = solver.getTime();
            float angle = Definition::pi;
            // float angle = maxAngle * sin(time) + Definition::pi * 0.5;
            // angle += Definition::pi * 1.f;
            solver.setObjectVelocity(object, objectSpawnSpeed * sf::Vector2f(cos(angle), sin(angle)));
            object.color = getRainbow(time);
        }

        solver.update();
    }

    void Verlet_Demo::draw(float /*delta*/){
        const sf::Vector3f constraint = solver.getConstraint();
        sf::CircleShape constraintBackground{constraint.z};
        constraintBackground.setOrigin(constraint.z, constraint.z);
        constraintBackground.setFillColor({50, 50, 50});
        constraintBackground.setPosition(constraint.x, constraint.y);
        constraintBackground.setPointCount(128);
        engine->window.draw(constraintBackground);

        sf::CircleShape circle{1.f};
        circle.setPointCount(32);
        circle.setOrigin(1.f,1.f);
        const auto& objects = solver.getObjects();
        for(const auto& object : objects){
            circle.setPosition(object.pos);
            circle.setScale(object.radius, object.radius);
            circle.setFillColor(object.color);
            engine->window.draw(circle);
        }
    }
}