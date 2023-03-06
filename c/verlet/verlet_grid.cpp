#include "../../h/verlet/verlet_grid.hpp"
#include <iostream>

namespace VeX{
    Verlet_Grid::Verlet_Grid(const sf::Vector2f & gridSize, float cellSize, const sf::Vector2f & gridPos):
            gridDimensions(gridSize.x/cellSize, gridSize.y/cellSize), // Narrowing to Vector2i
            cellSize{cellSize},
            gridPos{gridPos}
        {}

    void Verlet_Grid::emplace(const std::vector<std::shared_ptr<Verlet_Object>> & objects){
        std::cout << "VG::emplace\n";
        for(auto& object : objects){
            sf::Vector2i cellPos = posToCellPos(object->pos);
            if(cellPos.x < 0 or cellPos.y < 0 or cellPos.x >= gridDimensions.x or cellPos.y >= gridDimensions.y){
                continue;
            }
            std::vector<std::shared_ptr<Verlet_Object>> & cell = grid[(cellPos.x * 1000) + cellPos.y];
            cell.emplace_back(object);
        }
    }

    void Verlet_Grid::clear(){
        std::cout << "VG::clear\n";
        grid.clear();
    }
    
    void Verlet_Grid::checkCollisions(){
        std::cout << "VG::checkCollisions\n";
        for(int x{0}; x < gridDimensions.x-1; x++){
            for(int y{0}; y < gridDimensions.y-1; y++){
                auto cell = getCellContents({x,y});
                // for(int dx{0}; dx < 2; dx++){
                //     for(int dy{0}; dy < 2; dy++){
                //         auto otherCell = getCellContents({x+dx, y+dy});
                //         //checkCellCollisions(cell, otherCell);
                //     }
                // }
            }
        }
    }

    void Verlet_Grid::checkCellCollisions(std::vector<std::shared_ptr<Verlet_Object>> & cell1, std::vector<std::shared_ptr<Verlet_Object>> & cell2){
        std::cout << "VG::checkCellCollisions\n";
        const float responseCoefficient = 0.75f;
        for(auto& object1 : cell1){
            for(auto& object2 : cell2){
                if(object1 != object2){
                    const sf::Vector2f difference = object1->pos - object2->pos;
                    const float distanceSquared = difference.x * difference.x + difference.y * difference.y;
                    const float combinedRadius = object1->radius + object2->radius;
                    if(distanceSquared < combinedRadius * combinedRadius){
                        const float distance = sqrt(distanceSquared); // sqrt is expensive, and we only need the actual distance if they are colliding, so we calculate it here rather than wasting time on all checks.
                        const sf::Vector2f collisionNormal = difference / distance;
                        const float massRatio1 = object1->radius / (object1->radius + object2->radius); // We assume density to be equal across objects.
                        const float massRatio2 = object2->radius / (object2->radius + object1->radius); // We assume density to be equal across objects.
                        const float delta = 0.5f * responseCoefficient * (distance - combinedRadius);

                        object1->pos -= collisionNormal * (massRatio2 * delta);
                        object2->pos += collisionNormal * (massRatio1 * delta);
                    }
                }
            }
        }
    }


    std::vector<std::shared_ptr<Verlet_Object>> Verlet_Grid::getCellContents(const sf::Vector2i & cellPos){
        std::cout << cellPos << "\n";
        try{
            return grid.at((cellPos.x * 1000) + cellPos.y);
        }catch(std::out_of_range){
            std::cout << "bad\n";
            return {};
        }
    }

    sf::Vector2i Verlet_Grid::posToCellPos(const sf::Vector2f & pos) const {
        auto relativePos = pos - gridPos;
        return sf::Vector2i(relativePos.x, relativePos.y);
    }
}