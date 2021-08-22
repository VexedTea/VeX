#ifndef __VOXEL_HPP__
#define __VOXEL_HPP__

#include <memory>
#include "SFML/graphics.hpp"

#include "color_gradient.hpp"

namespace VeX{

    class Voxel;

    struct Voxel_Neighbours{
        std::shared_ptr<Voxel> upLeft;
        std::shared_ptr<Voxel> up;
        std::shared_ptr<Voxel> upRight;
        std::shared_ptr<Voxel> left;
        std::shared_ptr<Voxel> right;
        std::shared_ptr<Voxel> underLeft;
        std::shared_ptr<Voxel> under;
        std::shared_ptr<Voxel> underRight;
    };

    class Voxel{
    private:
        sf::Vector2f position;
        sf::Vector2f size;
        float value;
        Color_Gradient gradient;

        sf::Sprite sprite;
        Voxel_Neighbours neighbours;

    public:
        Voxel(const sf::Vector2f & position, const sf::Vector2f & size):
            position(position),
            size(size),
            value(0.f),
            gradient({sf::Color(0,0,0,0), sf::Color(255,255,255,255)}),
            sprite(engine->getBlankTexture())
        {
            sprite.setPosition(position);
            sprite.setScale(size);
            sprite.setColor(sf::Color(0,0,0,0));
        }

        Voxel(){}//NULL constructor

        void draw(){
            engine->window.draw(sprite);
        }

        void registerNeighbour(const std::shared_ptr<Voxel> & /* neighbour */){

        }

        void setValue(float newValue){
            value = newValue;
            sprite.setColor(gradient.getColorAt(value));
        }
    };

} // namespace VeX

#endif // __VOXEL_HPP__
