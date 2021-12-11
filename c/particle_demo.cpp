#include "../h/particle_demo.hpp"

namespace VeX{

    Particle_Demo::Particle_Demo(bool snapToScreenCenter, bool circlePaused):
        snapToScreenCenter(snapToScreenCenter),
        circlePaused(circlePaused),
        showCenters(false),
        drawParticles(true),
        maxParticleCountReached(false),
        circleAngle(0.f),
        primitiveTypeIndex(0),
        primitiveTypes({sf::PrimitiveType::Points, sf::PrimitiveType::Lines, sf::PrimitiveType::LineStrip, sf::PrimitiveType::Triangles, sf::PrimitiveType::TriangleStrip, sf::PrimitiveType::TriangleFan, sf::PrimitiveType::Quads}),
        particleSystems()
    {}

    void Particle_Demo::init(){
        engine->addKeybind("resetState", sf::Keyboard::Key::Backspace, KeybindCondition::OnKeyDown, 
            [&](){
                engine->settings->currentParticleCount = 0;
                engine->addState(std::make_unique<VeX::Particle_Demo>(snapToScreenCenter), true);
            });
        engine->addKeybind("snapToScreenCenterToggle", sf::Keyboard::Key::O, KeybindCondition::OnKeyDown, 
            [&](){
                snapToScreenCenter = !snapToScreenCenter;
            });
        engine->addKeybind("circlePauseToggle", sf::Keyboard::Key::P, KeybindCondition::OnKeyDown, 
            [&](){
                circlePaused = !circlePaused;
            });
        engine->addKeybind("showCenters", sf::Keyboard::Key::L, KeybindCondition::OnKeyDown, 
            [&](){
                showCenters = !showCenters;
            });
        engine->addKeybind("drawParticles", sf::Keyboard::Key::K, KeybindCondition::OnKeyDown, 
            [&](){
                drawParticles = !drawParticles;
            });
        engine->addKeybind("nextPrimitiveType", sf::Keyboard::Key::Add, KeybindCondition::OnKeyDown, 
            [&](){
                if(primitiveTypeIndex >= primitiveTypes.size()-1){
                    primitiveTypeIndex = 0;
                }else{
                    primitiveTypeIndex++;
                }
                for(unsigned int i=0; i<particleSystems.size(); i++){
                    particleSystems[i]->setPrimitiveType(primitiveTypes[primitiveTypeIndex]);
                }
            });
        engine->addKeybind("prevPrimitiveType", sf::Keyboard::Key::Subtract, KeybindCondition::OnKeyDown, 
            [&](){
                if(primitiveTypeIndex < 1){
                    primitiveTypeIndex = primitiveTypes.size()-1;
                }else{
                    primitiveTypeIndex--;
                }
                for(unsigned int i=0; i<particleSystems.size(); i++){
                    particleSystems[i]->setPrimitiveType(primitiveTypes[primitiveTypeIndex]);
                }
            });
        for(unsigned int i=0; i<6; i++){
            particleSystems.push_back(std::make_unique<Particle_System_Thread>());
        }
        auto shader = engine->loadShader("particleTextureMap", "assets/shaders/particle_texture_map");
        shader->setUniform("texture", engine->loadTexture("testImage", "assets/textures/test_image.png"));
    }

    void Particle_Demo::handleInput(){
        sf::Event event;
        while (engine->window.pollEvent(event)){
            if (event.type == sf::Event::Closed)
                engine->window.close();
        }
    }

    void Particle_Demo::update(float delta){
        sf::Vector2f circleCenter;
        if(!snapToScreenCenter){
            circleCenter = vector2iToVector2f(sf::Mouse::getPosition(engine->window));
        }else{
            circleCenter = engine->settings->getScreenCenter();
        }
        
        if(!circlePaused){
            for(unsigned int i=0; i<particleSystems.size(); i++){
                particleSystems[i]->setPosition(getPositionOnCircle(circleCenter, 400.f, circleAngle + (i * (360.f/particleSystems.size()))));
            }
            circleAngle += 1.65 * 360.f * delta;
            if(circleAngle >= 360.f){
                circleAngle -= 360.f;
            }   //0.215 & 500.f highest known to inhibit effect and 0.191 smallest known
        }

        if(!maxParticleCountReached && engine->getFramerate() > 75.f && engine->settings->currentParticleCount < 500'000){
            for(unsigned int i=0; i<25; i++){
                for(unsigned int i=0; i<particleSystems.size(); i++){
                    particleSystems[i]->addParticle(std::make_unique<Particle>(particleSystems[i]->getPosition() + sf::Vector2f{-100 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/(100*2))),
                                                                                    -100 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/(100*2)))}, Definition::defaultParticleMotionDampening,
                                                                                    Color_Gradient({{102, 31, 196}, {21, 232, 255}, {255,255,255}}), 3500.f));
                }
                engine->settings->currentParticleCount += particleSystems.size();
            }
        }else if(engine->getFramerate() < 62.f){
            for(unsigned int i=0; i<particleSystems.size(); i++){
                particleSystems[i]->removeOldestParticle();
            }
            engine->settings->currentParticleCount -= particleSystems.size();
            maxParticleCountReached = true;
        }else{
            maxParticleCountReached = true;
        }
        for(unsigned int i=0; i<particleSystems.size(); i++){
            particleSystems[i]->update(delta);
        }
        for(unsigned int i=0; i<particleSystems.size(); i++){
            particleSystems[i]->waitForUpdateDone();
        }
    }

    void Particle_Demo::draw(float delta){
        if(drawParticles){
            for(unsigned int i=0; i<particleSystems.size(); i++){
                particleSystems[i]->draw(delta, *engine->loadVertexShader("particleTextureMap", "assets/shaders/particle_texture_map"));
            }
        }
        
        if(showCenters){
            for(unsigned int i=0; i<particleSystems.size(); i++){
                particleSystems[i]->drawCenterPoint();
            }
        }

        engine->displayFramerate();
        engine->displayCurrentParticleCount();
    }

    void Particle_Demo::pause(){
        for(unsigned int i=0; i<particleSystems.size(); i++){
            particleSystems[i]->pause();
        }
    }

    void Particle_Demo::resume(){
        for(unsigned int i=0; i<particleSystems.size(); i++){
            particleSystems[i]->resume();
        }
    }

    void Particle_Demo::stop(){
        engine->settings->currentParticleCount = 0;
    }

} // namespace VeX
