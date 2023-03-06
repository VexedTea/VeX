#ifndef __GRID_HPP__
#define __GRID_HPP__

#include <map>
#include <vector>
#include <memory>
//#include <utility>
#include <SFML/Graphics.hpp>
#include "verlet_object.hpp"
#include "../utilities.hpp"

namespace VeX{

    class Verlet_Grid{
    public:
        Verlet_Grid(const sf::Vector2f & gridSize, float cellSize, const sf::Vector2f & gridPos);

        void emplace(const std::vector<std::shared_ptr<Verlet_Object>> & objects);

        void clear();

        void checkCollisions();

        void checkCellCollisions(std::vector<std::shared_ptr<Verlet_Object>> & cell1, std::vector<std::shared_ptr<Verlet_Object>> & cell2);

        [[nodiscard]]
        std::vector<std::shared_ptr<Verlet_Object>> getCellContents(const sf::Vector2i & cellPos);

        [[nodiscard]]
        sf::Vector2i posToCellPos(const sf::Vector2f & pos) const;

    private:
        std::map<int, std::vector<std::shared_ptr<Verlet_Object>>> grid;
        sf::Vector2i gridDimensions;
        float cellSize;
        sf::Vector2f gridPos;
    };

} // namespace VeX

#endif // __GRID_HPP__
