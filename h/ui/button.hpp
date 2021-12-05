#ifndef __BUTTON_HPP__
#define __BUTTON_HPP__

#include "../transform_util.hpp"

#include "SFML/Graphics.hpp"
#include <functional>

namespace VeX{
namespace UI{

    struct Button_Data{
        std::string text;
    };

    struct Button_Textures{
        const sf::Texture & base;
        const sf::Texture & highlighted;
        const sf::Texture & pressed;
    };

    enum class Button_States{
        Base,
        Highlighted,
        Pressed
    };

    class Button{
    private:
        sf::Sprite sprite;
        Button_Textures textures;
        std::function<void()> action;
        Button_Data buttonData;
        sf::Vector2f pos;
        sf::Vector2f scale;

        Button_States state;
        sf::Font buttonFont;
        sf::Text buttonText;
    public:
        Button(const Button_Data & buttonData, const sf::Vector2f & pos, const sf::Vector2f scale, const Button_Textures & textures, std::function<void()> action);

        Button(const Button_Data & buttonData, const Button_Textures & textures, const std::function<void()> & action);

        bool contains(const sf::Vector2f & pos);

        void update(float delta);

        void draw(float delta);

        void snapTo(const sf::Vector2f & position, const sf::Vector2f scale_);
    };

} // namespace UI
} // namespace VeX

#endif // __BUTTON_HPP__
