#include "../h/progress_bar.hpp"

namespace VeX{

    Progress_Bar::Progress_Bar(const std::string & name, const sf::Vector2f & position, const sf::Vector2i & size, int edge, const Color_Gradient & gradient, const sf::Color & backgroundColor):
        Sprite_Object(position-sf::Vector2f(edge,edge), engine->makeRectangleTexture(name + "_bg", size+sf::Vector2i(edge*2,edge*2), backgroundColor)),
        size(size),
        edge(edge),
        progress(0),
        bar(engine->makeRectangleTexture(name + "_bar", size, gradient)),
        cover(engine->makeRectangleTexture(name + "_cover", sf::Vector2i(1,size.y), backgroundColor))
    {}

    Progress_Bar::Progress_Bar(const std::string & name, const sf::Vector2f & position, const sf::Vector2i & size, int edge, const Color_Gradient & gradient):
        Progress_Bar(name, position, size, edge, gradient, sf::Color(50,50,50))
    {}

    Progress_Bar::Progress_Bar(const std::string & name, const sf::Vector2f & position, const sf::Vector2i & size, const Color_Gradient & gradient):
        Progress_Bar(name, position, size, 0, gradient, sf::Color(50,50,50))
    {}

    Progress_Bar::Progress_Bar(const std::string & name, const sf::Vector2f & position, const sf::Vector2i & size):
        Progress_Bar(name, position, size, 0, Definition::vexGradient, sf::Color(50,50,50))
    {}

    void Progress_Bar::setProgress(float newProgress){
        progress = newProgress;
    }

    void Progress_Bar::addProgress(float addition){
        progress += addition;
    }

    void Progress_Bar::draw(){
        draw(0.f);
    }

    void Progress_Bar::draw(float delta){
        Sprite_Object::draw(delta);
        bar.setPosition(position+sf::Vector2f(edge,edge));
        engine->window.draw(bar);
        cover.setScale({size.x-(progress*size.x),1.f});
        cover.setPosition(sf::Vector2f(position.x+(progress*size.x), position.y)+sf::Vector2f(edge,edge));
        engine->window.draw(cover);
    }

} // namespace VeX
