#ifndef __PROGRESS_BAR_HPP__
#define __PROGRESS_BAR_HPP__

#include "sprite_object.hpp"
#include "color_gradient.hpp"
#include "engine.hpp"

namespace VeX{

    class Progress_Bar : public Sprite_Object{
    private:
        sf::Vector2i size;
        int edge;
        float progress;
        sf::Sprite bar;
        sf::Sprite cover;
    public:
        Progress_Bar(const std::string & name, const sf::Vector2f & position, const sf::Vector2i & size, int edge, const Color_Gradient & gradient, const sf::Color & backgroundColor);

        Progress_Bar(const std::string & name, const sf::Vector2f & position, const sf::Vector2i & size, int edge, const Color_Gradient & gradient);

        Progress_Bar(const std::string & name, const sf::Vector2f & position, const sf::Vector2i & size, const Color_Gradient & gradient);

        Progress_Bar(const std::string & name, const sf::Vector2f & position, const sf::Vector2i & size);

        void setProgress(float newProgress);

        void addProgress(float addition);

        void draw();

        void draw(float delta)override;
    };

} // namespace VeX

#endif // __PROGRESS_BAR_HPP__
