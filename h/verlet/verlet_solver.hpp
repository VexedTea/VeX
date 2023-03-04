#ifndef __SOLVER_HPP__
#define __SOLVER_HPP__

#include "verlet_object.hpp"
#include <cmath>
#include <vector>

namespace VeX{

    class Verlet_Solver{
    public:
        void update();

        Verlet_Object& addObject(const sf::Vector2f & pos, float radius);

        void setSimulationUpdateRate(float rate);

        void setConstraint(const sf::Vector2f & pos, float radius);

        void setSubStepCount(int count);

        void setObjectVelocity(Verlet_Object& object, const sf::Vector2f & velocity);

        [[nodiscard]]
        const std::vector<Verlet_Object> & getObjects() const;

        [[nodiscard]]
        sf::Vector3f getConstraint() const;

        [[nodiscard]]
        int getObjectCount() const;

        [[nodiscard]]
        float getTime() const;

        [[nodiscard]]
        float getStepDeltaTime() const;

    private:
        int subSteps = 1;
        sf::Vector2f gravity = {0.f, 1000.f};
        sf::Vector2f constraintCenter;
        float constraintRadius = 100.f;
        std::vector<Verlet_Object> objects;
        float time = 0.f;
        float frameDeltaTime = 0.f;

        void applyGravity();

        void checkCollisions();

        void applyConstraint();

        void updateObjects(float dt);
    };

} // namespace VeX

#endif // __SOLVER_HPP__
