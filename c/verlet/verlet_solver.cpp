#include "../../h/verlet/verlet_solver.hpp"

namespace VeX{
    void Verlet_Solver::update(){
        time += frameDeltaTime;
        const float stepDeltaTime = getStepDeltaTime();
        for(int i{0}; i < subSteps; i++){
            applyGravity();
            checkCollisions();
            applyConstraint();
            updateObjects(stepDeltaTime);
        }
    }

    Verlet_Object& Verlet_Solver::addObject(const sf::Vector2f & pos, float radius){
        return objects.emplace_back(pos, radius);
    }

    void Verlet_Solver::setSimulationUpdateRate(float rate){
        frameDeltaTime = 1.f / rate;
    }

    void Verlet_Solver::setConstraint(const sf::Vector2f & pos, float radius){
        constraintCenter = pos;
        constraintRadius = radius;
    }

    void Verlet_Solver::setSubStepCount(int count){
        subSteps = count;
    }

    void Verlet_Solver::setObjectVelocity(Verlet_Object& object, const sf::Vector2f & velocity){
        object.setVelocity(velocity, getStepDeltaTime());
    }

    const std::vector<Verlet_Object> & Verlet_Solver::getObjects() const {
        return objects;
    }

    sf::Vector3f Verlet_Solver::getConstraint() const {
        return {constraintCenter.x, constraintCenter.y, constraintRadius};
    }

    int Verlet_Solver::getObjectCount() const {
        return objects.size();
    }

    float Verlet_Solver::getTime() const {
        return time;
    }

    float Verlet_Solver::getStepDeltaTime() const {
        return frameDeltaTime / static_cast<float>(subSteps);
    }

    void Verlet_Solver::applyGravity(){
        for(auto& object : objects){
            object.accelerate(gravity);
        }
    }

    void Verlet_Solver::checkCollisions(){
        const float responseCoefficient = 0.75f;
        const int objectCount = objects.size();

        for(int i{0}; i < objectCount; i++){
            Verlet_Object& object1 = objects[i];
            for(int j{i + 1}; j < objectCount; j++){
                Verlet_Object& object2 = objects[j];
                const sf::Vector2f difference = object1.pos - object2.pos;
                const float distanceSquared = difference.x * difference.x + difference.y * difference.y;
                const float combinedRadius = object1.radius + object2.radius;
                if(distanceSquared < combinedRadius * combinedRadius){
                    const float distance = sqrt(distanceSquared); // sqrt is expensive, and we only need the actual distance if they are colliding, so we calculate it here rather than wasting time on all checks.
                    const sf::Vector2f collisionNormal = difference / distance;
                    const float massRatio1 = object1.radius / (object1.radius + object2.radius); // We assume density to be equal across objects.
                    const float massRatio2 = object2.radius / (object2.radius + object1.radius); // We assume density to be equal across objects.
                    const float delta = 0.5f * responseCoefficient * (distance - combinedRadius);

                    object1.pos -= collisionNormal * (massRatio2 * delta);
                    object2.pos += collisionNormal * (massRatio1 * delta);
                }
            }
        }
    }

    void Verlet_Solver::applyConstraint(){
        for(auto& object : objects){
            const sf::Vector2f difference = constraintCenter - object.pos;
            const float distanceSquared = difference.x * difference.x + difference.y * difference.y;
            const float radiusDifference = constraintRadius - object.radius;
            if(distanceSquared > radiusDifference * radiusDifference){
                const float distance = sqrt(distanceSquared); // sqrt is expensive, and we only need the actual distance if they are colliding, so we calculate it here rather than wasting time on all checks.
                const sf::Vector2f normal = difference / distance;
                object.pos = constraintCenter - normal * radiusDifference;
            }
        }
    }

    void Verlet_Solver::updateObjects(float dt){
        for(auto& object : objects){
            object.update(dt);
        }
    }
}