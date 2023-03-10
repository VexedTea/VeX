// #ifndef __GRID_HPP__
// #define __GRID_HPP__

// #include <vector>
// #include <memory>
// #include <array>
// #include <SFML/Graphics.hpp>
// #include "verlet_object.hpp"
// #include "../utilities.hpp"

// namespace VeX{

//     class Verlet_Grid{
//     public:
//         Verlet_Grid(const sf::Vector2f & gridSize, float cellSize, const sf::Vector2f & gridPos);

//         void emplace(std::vector<Verlet_Object> & objects);

//         void clear();

//         void applyGravity();

//         void checkCollisions();

//         void checkCellCollisions(std::vector<Verlet_Object> & cell1, std::vector<Verlet_Object> & cell2);

//         void applyConstraint(const sf::Vector2f & constraintCenter);

//         [[nodiscard]]
//         std::vector<Verlet_Object> getCellContents(const sf::Vector2i & cellPos);

//         [[nodiscard]]
//         sf::Vector2i posToCellPos(const sf::Vector2f & pos) const;

//     private:
//         sf::Vector2i gridDimensions;
//         float cellSize;
//         sf::Vector2f gridPos;

//         std::unique_ptr<std::array<std::array<std::vector<Verlet_Object>, 4096>, 4096>> grid;
//         std::unique_ptr<std::array<std::array<std::vector<Verlet_Object>, 4096>, 4096>> inactiveGrid;

//         void swapGrids();
//     };

// } // namespace VeX

// #endif // __GRID_HPP__
