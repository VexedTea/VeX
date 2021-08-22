#include <iostream>
#include <memory>
#include "SFML/Graphics.hpp"
#include "../h/engine.hpp"
#include "../h/definitions.hpp"
#include "../h/object.hpp"

//States
#include "../h/splash_screen.hpp"
#include "../h/particle_demo.hpp"
//#include "../h/multithreaded_particle_demo.hpp"
#include "../h/slideshow.hpp"
#include "../h/grav.hpp"
#include "../h/particle_experiments.hpp"
#include "../h/voxel_sim_demo.hpp"

int main(){
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    VeX::engine->window.create(desktop, "VeX", sf::Style::None /*sf::Style::Close | sf::Style::Titlebar | sf::Style::Fullscreen*/);
    sf::Image icon;
    icon.loadFromFile("assets/textures/VexedTea.png");
    VeX::engine->window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    VeX::engine->settings->screenWidth = desktop.width;
    VeX::engine->settings->screenHeight = desktop.height;

    srand(time(NULL));
    
    //VeX::engine->addState(std::make_unique<VeX::Splash_Screen>(sf::seconds(3.f), std::make_unique<VeX::Slideshow>("assets/textures")), false);
    //VeX::engine->addState(std::make_unique<VeX::Splash_Screen>(sf::seconds(3.f), std::make_unique<VeX::Particle_Demo>()), false);
    //VeX::engine->addState(std::make_unique<VeX::Splash_Screen>(sf::seconds(3.f), std::make_unique<VeX::Grav>()), false);
    //VeX::engine->addState(std::make_unique<VeX::Splash_Screen>(sf::seconds(1.f), std::make_unique<VeX::Particle_Experiments>()), false);
    VeX::engine->addState(std::make_unique<VeX::Splash_Screen>(sf::seconds(1.f), std::make_unique<VeX::Voxel_Sim_Demo>()), false);
    VeX::engine->run();

    //Can do stuff here to be done when closing, like saving a config/savefile or smth
    //std::cout << "Highest frame time (longest frame): " << VeX::engine->highestFrameTime << " and in fps: " << 1.f/VeX::engine->highestFrameTime << std::endl;
}