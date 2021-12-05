#include "../../h/ui/button.hpp"

namespace VeX{
namespace UI{

    Button::Button(const Button_Data & buttonData, const sf::Vector2f & pos, const sf::Vector2f scale, const Button_Textures & textures, std::function<void()> action):
        sprite{textures.base},
        textures{textures},
        action{action},
        buttonData{buttonData},
        pos{pos},
        scale{scale},
        state{Button_States::Base}
    {
        sprite = util::snapTo(sprite, pos, scale);
        //sprite.setColor(sf::Color(255,0,0,100));
        if(!buttonFont.loadFromFile("assets/fonts/Arial_GEO.TTF")){
            std::cout << "Engine: Failed to load buttonFont" << std::endl;
        }
        buttonText.setFont(buttonFont);
        buttonText.setString(buttonData.text);
        buttonText.setCharacterSize(24);
        buttonText.setFillColor(sf::Color::White);
        buttonText.setOutlineThickness(3);
        buttonText.setOutlineColor(sf::Color::Black);
    }

    Button::Button(const Button_Data & buttonData, const Button_Textures & textures, const std::function<void()> & action):
        Button(buttonData, {0.f, 0.f}, {1.f, 1.f}, textures, action)
    {}

    bool Button::contains(const sf::Vector2f & pos){
        return sprite.getGlobalBounds().contains(pos);
    }

    void Button::update(float){
        switch(state){
            case Button_States::Base:
                buttonText.setFillColor(sf::Color::White);
                if(contains(engine->getMousePos(engine->window))){
                    if(engine->onLeftClickRelease()){
                        sprite.setTexture(textures.pressed);
                        sprite = util::snapTo(sprite, pos, scale);
                        state = Button_States::Pressed;
                    }else{
                        sprite.setTexture(textures.highlighted);
                        sprite = util::snapTo(sprite, pos, scale);
                        state = Button_States::Highlighted;
                    }
                }
                break;
            case Button_States::Highlighted:
                buttonText.setFillColor(sf::Color{21, 232, 255});
                if(!contains(engine->getMousePos(engine->window))){
                    sprite.setTexture(textures.base);
                    sprite = util::snapTo(sprite, pos, scale);
                    state = Button_States::Base;
                }else if(engine->onLeftClickRelease()){
                    sprite.setTexture(textures.pressed);
                    sprite = util::snapTo(sprite, pos, scale);
                    state = Button_States::Pressed;
                }
                break;
            case Button_States::Pressed:
                action();
                if(!contains(engine->getMousePos(engine->window))){
                    sprite.setTexture(textures.base);
                    sprite = util::snapTo(sprite, pos, scale);
                    state = Button_States::Base;
                }else{
                    sprite.setTexture(textures.highlighted);
                    sprite = util::snapTo(sprite, pos, scale);
                    state = Button_States::Highlighted;
                }
        }
    }

    void Button::draw(float){
        engine->window.draw(sprite);
        buttonText.setFont(buttonFont);
        engine->window.draw(buttonText);
    }

    void Button::snapTo(const sf::Vector2f & position, const sf::Vector2f scale_){
        pos = position;
        scale = scale_;
        sprite = util::snapTo(sprite, pos, scale);
        buttonText.setFont(buttonFont);
        buttonText.setPosition(sprite.getPosition());
        buttonText.setOrigin(buttonText.getLocalBounds()|2.f);
    }

} // namespace UI
} // namespace VeX
