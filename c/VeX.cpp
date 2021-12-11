#include <iostream>
#include <memory>
#include "SFML/Graphics.hpp"
#include "../h/engine.hpp"
#include "../h/definitions.hpp"
#include "../h/object.hpp"

//States
#include "../h/pause_menu.hpp"
#include "../h/splash_screen.hpp"
#include "../h/demo/particle_demo.hpp"
#include "../h/demo/grav.hpp"
#include "../h/demo/ptm_shader_demo.hpp"

int main(){
    if (!sf::Shader::isAvailable()){
        std::cout << "Fatal: No shader support on system.\n";
        exit(1);
    }

    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    VeX::engine->window.create(desktop, "VeX", sf::Style::None /*sf::Style::Close | sf::Style::Titlebar | sf::Style::Fullscreen*/);
    sf::Image icon;
    icon.loadFromFile("assets/textures/VexedTea.png");
    VeX::engine->window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    VeX::engine->settings->screenWidth = desktop.width;
    VeX::engine->settings->screenHeight = desktop.height;
    auto pauseMenu = std::make_unique<VeX::Pause_Menu>();
    pauseMenu->addStateSelection(
        [](){return std::make_unique<VeX::Particle_Demo>();},
        {"Particle Demo"}
    );
    pauseMenu->addStateSelection(
        [](){return std::make_unique<VeX::Grav>();},
        {"Grav"}
    );
    pauseMenu->addStateSelection(
        [](){return std::make_unique<VeX::PTM_Shader_Demo>();},
        {"Particle Texture Mapping Shader Demo"}
    );
    VeX::engine->registerPauseMenu(std::move(pauseMenu));

    VeX::engine->addState(std::make_unique<VeX::Splash_Screen>(sf::seconds(1.5), std::make_unique<VeX::Particle_Demo>()), false);
    VeX::engine->run();

    //Can do stuff here to be done when closing, like saving a config/savefile or smth
    //std::cout << "Highest frame time (longest frame): " << VeX::engine->highestFrameTime << " and in fps: " << 1.f/VeX::engine->highestFrameTime << std::endl;
}