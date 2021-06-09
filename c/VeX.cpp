#include <iostream>
#include <memory>
#include "SFML/Graphics.hpp"
#include "../h/sierpinski.hpp"
#include "../h/particle_demo.hpp"
#include "../h/engine.hpp"
#include "../h/definitions.hpp"

int main(){
    sf::RenderWindow window;
    window.create(sf::VideoMode(Definition::screenWidth, Definition::screenHeight), "VeX", sf::Style::Close | sf::Style::Titlebar /*| sf::Style::Fullscreen*/);

    srand(time(NULL));

    VeX::Engine engine(window); 
    engine.addState(std::make_unique<VeX::Particle_Demo>(engine), false);
    engine.run();
}