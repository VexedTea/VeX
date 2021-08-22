#ifndef __VOXEL_SIM_HPP__
#define __VOXEL_SIM_HPP__

#include <vector>

#include "object.hpp"
#include "voxel.hpp"

namespace VeX{

    class Voxel_Sim{
    private:
        sf::Vector2f position;
        sf::Vector2i size;
        int voxelSize;
        std::vector<std::vector<std::shared_ptr<Voxel>>> voxels;
    public:
        Voxel_Sim(const sf::Vector2f position, const sf::Vector2u size, unsigned int voxelSize):
            position(position),
            size(size),
            voxelSize(voxelSize)
        {
            voxels.resize(size.x/voxelSize);
            for(unsigned int i=0; i<size.x/voxelSize; i++){
                voxels[i].resize(size.y/voxelSize);
                for(unsigned int j=0; j<size.y/voxelSize; j++){
                    voxels[i][j] = std::make_shared<Voxel>(sf::Vector2f(i*voxelSize, j*voxelSize), sf::Vector2f(voxelSize, voxelSize));
                    //voxels[i][j]->setValue(static_cast <float> (rand()) / (static_cast <float> (RAND_MAX)));
                }
            }
        }

        Voxel_Sim(const sf::Vector2f position, unsigned int voxelSize):
            Voxel_Sim(position, sf::Vector2u(engine->settings->screenWidth, engine->settings->screenHeight), voxelSize)
        {}

        Voxel_Sim(const sf::Vector2f position):
            Voxel_Sim(position, sf::Vector2u(engine->settings->screenWidth, engine->settings->screenHeight), 1)
        {}

        Voxel_Sim(unsigned int voxelSize):
            Voxel_Sim(sf::Vector2f(0.f,0.f), voxelSize)
        {}

        Voxel_Sim():
            Voxel_Sim(sf::Vector2f(0.f,0.f))
        {}

        void update(float ){

        }

        void draw(){
            for(unsigned int i=0; i<voxels.size(); i++){
                for(unsigned int j=0; j<voxels[i].size(); j++){
                    voxels[i][j]->draw();
                }
            }
        }
    };

} // namespace VeX

#endif // __VOXEL_SIM_HPP__
