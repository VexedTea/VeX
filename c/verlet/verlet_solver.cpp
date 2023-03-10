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
            swapGrids();
        }
    }

    Verlet_Object& Verlet_Solver::addObject(const sf::Vector2f & pos){
        // return objects.emplace_back(pos, objectRadius); 

        Verlet_Object object(pos, objectRadius);
        sf::Vector2i cellPos = worldSpaceToGridSpace(object.pos);
        if(cellPos.x < 0) cellPos.x = 0;
        if(cellPos.y < 0) cellPos.y = 0;
        if(cellPos.x >= gridDimensions.x) cellPos.x = gridDimensions.x - 1;
        if(cellPos.y >= gridDimensions.y) cellPos.y = gridDimensions.y - 1;
        std::vector<Verlet_Object> & cell = (*grid)[cellPos.x][cellPos.y];
        
        // Debug
        // for(int x{0}; x < gridDimensions.x-1; x++){
        //     for(int y{0}; y < gridDimensions.y-1; y++){
        //         //auto & cell = (*grid)[x][y];
        //         for(int dx{0}; dx < 2; dx++){
        //             for(int dy{0}; dy < 2; dy++){
        //                 std::cout << " x: "
        //                 << x << " y: "
        //                 << y << " dx: "
        //                 << dx << " dy: "
        //                 << dy << " x+dx: "
        //                 << (x+dx) << " y+dy: "
        //                 << (y+dy) << "\n";
        //             }
        //         }
        //     }
        // }
        // std::cout << worldSpaceToGridSpace({2560.f/2.f, 0.f}) << "\n";
        // std::cout << worldSpaceToGridSpace({2560.f/2.f, 1430.f}) << "\n";
        // std::cout << worldSpaceToGridSpace({2560.f/2.f, 1439.f}) << "\n";
        // std::cout << cellSize << "\n";
        // std::cout << gridDimensions << "\n";
        //

        return cell.emplace_back(object);
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

    std::unique_ptr<std::vector<Verlet_Object>> Verlet_Solver::getObjects() const {
        auto objects = std::make_unique<std::vector<Verlet_Object>>();
        for(int x{0}; x < gridDimensions.x; x++){
            for(int y{0}; y < gridDimensions.y; y++){
                for(auto & object : (*grid)[x][y]){
                    objects->emplace_back(object);
                }
            }
        }
        return objects;
    }

    sf::Vector3f Verlet_Solver::getConstraint() const {
        return {constraintCenter.x, constraintCenter.y, constraintRadius};
    }

    int Verlet_Solver::getObjectCount() const {
        int count{0};
        for(int x{0}; x < gridDimensions.x; x++){
            for(int y{0}; y < gridDimensions.y; y++){
                count += (*grid)[x][y].size();
            }
        }
        return count;
    }

    float Verlet_Solver::getTime() const {
        return time;
    }

    float Verlet_Solver::getStepDeltaTime() const {
        return frameDeltaTime / static_cast<float>(subSteps);
    }

    sf::Vector2i Verlet_Solver::worldSpaceToGridSpace(const sf::Vector2f & pos) const {
        // std::cout << pos << "<- pos\n";
        auto relativePos = (pos - gridPos) / cellSize;
        return sf::Vector2i(relativePos.x, relativePos.y);
    }

    void Verlet_Solver::swapGrids(){
        auto temp = std::move(grid);
        grid = std::move(inactiveGrid);
        inactiveGrid = std::move(temp);
    }

    void Verlet_Solver::applyGravity(){
        // for(auto& object : objects){
        //     object.accelerate(gravity);
        // }
        // grid.applyGravity();
        for(int x{0}; x < gridDimensions.x; x++){
            for(int y{0}; y < gridDimensions.y; y++){
                for(auto & object : (*grid)[x][y]){
                    object.accelerate(gravity);
                }
            }
        }
    }

    void Verlet_Solver::checkCollisions(){
        // std::cout << "pog\n";
        // grid.emplace(objects);
        // grid.checkCollisions();
        // grid.clear();

        // const float responseCoefficient = 0.75f;
        // const int objectCount = objects.size();

        // for(int i{0}; i < objectCount; i++){
        //     Verlet_Object& object1 = objects[i];
        //     for(int j{i + 1}; j < objectCount; j++){
        //         Verlet_Object& object2 = objects[j];
        //         const sf::Vector2f difference = object1.pos - object2.pos;
        //         const float distanceSquared = difference.x * difference.x + difference.y * difference.y;
        //         const float combinedRadius = object1.radius + object2.radius;
        //         if(distanceSquared < combinedRadius * combinedRadius){
        //             const float distance = sqrt(distanceSquared); // sqrt is expensive, and we only need the actual distance if they are colliding, so we calculate it here rather than wasting time on all checks.
        //             const sf::Vector2f collisionNormal = difference / distance;
        //             const float massRatio1 = object1.radius / (object1.radius + object2.radius); // We assume density to be equal across objects.
        //             const float massRatio2 = object2.radius / (object2.radius + object1.radius); // We assume density to be equal across objects.
        //             const float delta = 0.5f * responseCoefficient * (distance - combinedRadius);

        //             object1.pos -= collisionNormal * (massRatio2 * delta);
        //             object2.pos += collisionNormal * (massRatio1 * delta);
        //         }
        //     }
        // }

        for(int x{0}; x < gridDimensions.x; x++){
            for(int y{0}; y < gridDimensions.y; y++){
                auto & cell = (*grid)[x][y];
                for(int dx{0}; dx < 2; dx++){
                    for(int dy{0}; dy < 2; dy++){
                        // if(x+dx < 0 or x+dx > gridDimensions.x)continue;
                        // if(y+dy < 0 or y+dy > gridDimensions.y)continue;
                        auto & otherCell = (*grid)[x+dx][y+dy];
                        checkCellCollisions(cell, otherCell);
                    }
                }
                auto & otherCell = (*grid)[x+1][y-1];
                checkCellCollisions(cell, otherCell);
            }
        }
    }

    void Verlet_Solver::checkCellCollisions(std::vector<Verlet_Object> & cell1, std::vector<Verlet_Object> & cell2){
        // std::cout << "VG::checkCellCollisions\n";
        const float responseCoefficient = 1.f;
        
        // bool sameCell = (cell1 == cell2);
        // if(sameCell){
        //         std::cout << "pog";
        //     }
        // for(unsigned int i{0}; i < cell1.size(); i++){
        //     Verlet_Object& object1 = cell1[i];
        //     unsigned int jStart{0};
        //     if(sameCell){
        //         jStart = i + 1;
                // std::cout << "pog";
            // }
            // for(unsigned int j{jStart}; j < cell2.size(); j++){
            //     Verlet_Object& object2 = cell2[j];
        for(auto& object1 : cell1){
            // std::cout 
                // << gridDimensions 
                // << " "
                // << sameCell
                // << " 1: " 
                // << cell1.size()
                // << " "
                // << worldSpaceToGridSpace(object1.pos) 
                // << " " 
                // << object1.pos 
                // << "\n";
            for(auto& object2 : cell2){
                // std::cout
                // << " 2: "
                // << cell2.size()
                // << " "
                // << worldSpaceToGridSpace(object2.pos) 
                // << " " 
                // << object2.pos 
                // << "\n\n";
                // std::cout << "ok\n";
                if(object1 != object2){
                    //std::cout << "good\n";
                    // std::cout 
                    // << gridDimensions 
                    // << " "
                    // << sameCell
                    // << " 1: " 
                    // << cell1.size()
                    // << " "
                    // << worldSpaceToGridSpace(object1.pos) 
                    // << " " 
                    // << object1.pos 
                    // << " 2: "
                    // << cell2.size()
                    // << " "
                    // << worldSpaceToGridSpace(object2.pos) 
                    // << " " 
                    // << object2.pos 
                    // << "\n\n";
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
                        //std::cout << (-collisionNormal * (massRatio2 * delta)) << "\n";
                        // std::cout << "yes";
                        // std::cout << (cell1 == cell2) << "\n";
                        // std::cout << sameCell << "\n";
                        //if(!sameCell)std::cout<<"pog\n";
                    }
                }
            }
        }
    }

    void Verlet_Solver::applyConstraint(){
        for(int x{0}; x < gridDimensions.x; x++){
            for(int y{0}; y < gridDimensions.y; y++){
                for(auto & object : (*grid)[x][y]){
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
        }
    }

    void Verlet_Solver::updateObjects(float dt){
        for(int x{0}; x < gridDimensions.x; x++){
            for(int y{0}; y < gridDimensions.y; y++){
                for(auto object : (*grid)[x][y]){
                    object.update(dt);
                    sf::Vector2i cellPos = worldSpaceToGridSpace(object.pos);
                    // if(cellPos.x < 0) cellPos.x = 0;
                    // if(cellPos.y < 0) cellPos.y = 0;
                    // if(cellPos.x >= gridDimensions.x) cellPos.x = gridDimensions.x - 1;
                    // if(cellPos.y >= gridDimensions.y) cellPos.y = gridDimensions.y - 1;
                    std::vector<Verlet_Object> & cell = (*inactiveGrid)[cellPos.x][cellPos.y];
                    cell.emplace_back(object);
                }
                (*grid)[x][y].clear();
            }
        }
    }
}