#ifndef __SOLVER_HPP__
#define __SOLVER_HPP__

// #include "verlet_grid.hpp"
#include <memory>
#include <cmath>
#include <vector>
#include <array>
#include "verlet_object.hpp"
#include "../utilities.hpp"

namespace VeX{

    class Verlet_Solver{
    public:
        void update();

        Verlet_Object& addObject(const sf::Vector2f & pos);

        void setSimulationUpdateRate(float rate);

        void setConstraint(const sf::Vector2f & pos, float radius);

        void setSubStepCount(int count);

        void setObjectVelocity(Verlet_Object& object, const sf::Vector2f & velocity);

        [[nodiscard]]
        std::unique_ptr<std::vector<Verlet_Object>> getObjects() const;

        [[nodiscard]]
        sf::Vector3f getConstraint() const;

        [[nodiscard]]
        int getObjectCount() const;

        [[nodiscard]]
        float getTime() const;

        [[nodiscard]]
        float getStepDeltaTime() const;

        [[nodiscard]]
        sf::Vector2i worldSpaceToGridSpace(const sf::Vector2f & pos) const;

    private:
        int subSteps = 1;
        sf::Vector2f gravity = {0.f, 1000.f};
        sf::Vector2f constraintCenter;
        float constraintRadius = 100.f;
        float objectRadius = 5.7;
        // std::vector<Verlet_Object> objects;
        // Verlet_Grid grid{sf::Vector2f{1440.f, 1440.f}, objectRadius, sf::Vector2f{(2560.f-1440.f)/2.f, 0}};
        float time = 0.f;
        float frameDeltaTime = 0.f;

        // Grid
        float cellSize{objectRadius*2.f};
        sf::Vector2i gridDimensions = sf::Vector2i((1440.f/cellSize) + 1, (1440.f/cellSize) + 1);
        sf::Vector2f gridPos{(2560.f-1440.f)/2.f, 0};

        using Grid = std::array<std::array<std::vector<Verlet_Object>, 4096>, 4096>;
        std::unique_ptr<Grid> grid = std::make_unique<Grid>();
        std::unique_ptr<Grid> inactiveGrid = std::make_unique<Grid>();

        void swapGrids();
        //

        void applyGravity();

        void checkCollisions();

        void checkCellCollisions(std::vector<Verlet_Object> & cell1, std::vector<Verlet_Object> & cell2);

        void applyConstraint();

        void updateObjects(float dt);
    };

} // namespace VeX

#endif // __SOLVER_HPP__
