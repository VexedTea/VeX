#include <iostream>
#include <memory>
#include "SFML/Graphics.hpp"
#include "../h/engine.hpp"
#include "../h/definitions.hpp"
#include "../h/object.hpp"

//States
#include "../h/sierpinski.hpp"
#include "../h/particle_demo.hpp"
#include "../h/multithreaded_particle_demo.hpp"
#include "../h/slideshow.hpp"

int main(){
    VeX::window.create(sf::VideoMode(Definition::screenWidth, Definition::screenHeight), "VeX", sf::Style::Close | sf::Style::Titlebar /*| sf::Style::Fullscreen*/);

    srand(time(NULL));
    
    VeX::engine->addState(std::make_unique<VeX::Slideshow>("assets/textures"), false);
    VeX::engine->run();

    //Can do stuff here to be done when closing, like saving a config/savefile or smth
    std::cout << "Highest frame time (longest frame): " << VeX::engine->highestFrameTime << " and in fps: " << 1.f/VeX::engine->highestFrameTime << std::endl;
}