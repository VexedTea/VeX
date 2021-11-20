#include "../h/engine.hpp"

namespace VeX{

    Engine::Engine(sf::RenderWindow & window):
        State_Manager(),
        Asset_Manager(),
        pauseMenu(std::make_unique<Pause_Menu>()),
        delta(1.f/60.f),
        framerate(0.f),
        frametimes(60),
        //highestFrameTime(0),
        //startTime(clock.getElapsedTime().asSeconds()),
        pauseMenuOpen(false),
        window(window),
        settings(std::make_unique<Settings>())
    {
        if(!debugFont.loadFromFile("assets/fonts/Arial_GEO.TTF")){
            std::cout << "Engine: Failed to load debugFont" << std::endl;
        }
        frameTimeText.setFont(debugFont);
        frameTimeText.setString("First frame!");
        frameTimeText.setCharacterSize(24);
        frameTimeText.setFillColor(sf::Color::White);
        frameTimeText.setOutlineThickness(3);
        frameTimeText.setOutlineColor(sf::Color::Black);
        currentParticleCountText.setPosition(sf::Vector2f(0.f, 24.f));
        currentParticleCountText.setFont(debugFont);
        currentParticleCountText.setString(std::to_string(settings->currentParticleCount));
        currentParticleCountText.setCharacterSize(24);
        currentParticleCountText.setFillColor(sf::Color::White);
        currentParticleCountText.setOutlineThickness(3);
        currentParticleCountText.setOutlineColor(sf::Color::Black);
    }

    void Engine::runOnce(float & newTime, float & frameTime, float & interpolation, float & currentTime, float & accumulator){
        newTime = clock.getElapsedTime().asSeconds();
        frametimes.push_back(clock.getElapsedTime());
        frameTime = newTime - currentTime;
        if (frameTime > 0.25f) {
            frameTime = 0.25f;
        }
        currentTime = newTime;
        accumulator += frameTime;
        while (accumulator >= delta) {
            updateInputs();
            getActiveState()->handleInput();
            if(pauseMenuOpen){pauseMenu->handleInput();}
            getActiveState()->update(delta);
            if(pauseMenuOpen){pauseMenu->update(delta);}
            accumulator -= delta;
        }
        interpolation = accumulator/delta;

        framerate = 60.f/(frametimes.front().asSeconds() - frametimes.back().asSeconds());
        
        if(settings->clearWindow){window.clear(settings->backgroundColor);}
        getActiveState()->draw(interpolation);
        if(pauseMenuOpen){pauseMenu->draw(delta);}
        if(settings->drawWindow){window.display();}
    }

    void Engine::run(){ //Have a look at the frametiming stuff again
        float newTime, frameTime, interpolation;
        float currentTime = clock.getElapsedTime().asSeconds();
        float accumulator = 0.0f;
        pauseMenu->init();
        while (window.isOpen()){
            //std::cout << "run" << std::endl;
            processStateChanges();
            runOnce(newTime, frameTime, interpolation, currentTime, accumulator);
        }
    }

    void Engine::runPocketState(State_Ptr state){
        addState(std::move(state), false);
        processStateChanges();
        float newTime, frameTime, interpolation;
        float currentTime = clock.getElapsedTime().asSeconds();
        float accumulator = 0.0f;
        while (processStateChanges()){
            //std::cout << "run pocket" << std::endl;
            runOnce(newTime, frameTime, interpolation, currentTime, accumulator);
        }
        //std::cout << "end of runPocketState" << std::endl;
    }

    float Engine::getFramerate(){
        return framerate;
    }

    void Engine::displayFramerate(){
        frameTimeText.setString(std::to_string(framerate));
        window.draw(frameTimeText);
    }

    void Engine::displayCurrentParticleCount(){
        currentParticleCountText.setString(std::to_string(settings->currentParticleCount));
        window.draw(currentParticleCountText);
    }

    sf::RenderWindow window;
    VeX::Engine_Ptr engine = std::make_shared<VeX::Engine>(window);
}
