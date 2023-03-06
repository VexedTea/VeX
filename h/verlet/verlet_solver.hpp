#ifndef __SOLVER_HPP__
#define __SOLVER_HPP__

#include "verlet_object.hpp"
#include "verlet_grid.hpp"
#include <cmath>
#include <vector>
#include <array>
#include <memory>
#include "../utilities.hpp"

namespace VeX{

    class Verlet_Solver{
    public:
        void update();

        std::shared_ptr<Verlet_Object> addObject(const sf::Vector2f & pos);

        void setSimulationUpdateRate(float rate);

        void setConstraint(const sf::Vector2f & pos, float radius);

        void setSubStepCount(int count);

        void setObjectVelocity(std::shared_ptr<Verlet_Object> object, const sf::Vector2f & velocity);

        [[nodiscard]]
        const std::vector<std::shared_ptr<Verlet_Object>> & getObjects() const;

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
        float objectRadius = 10.f;
        std::vector<std::shared_ptr<Verlet_Object>> objects;
        Verlet_Grid grid{sf::Vector2f{1440.f, 1440.f}, objectRadius, sf::Vector2f{(2560.f-1440.f)/2.f, 0}};
        float time = 0.f;
        float frameDeltaTime = 0.f;

        void applyGravity();

        void checkCollisions();

        void applyConstraint();

        void updateObjects(float dt);
    };

} // namespace VeX

#endif // __SOLVER_HPP__
