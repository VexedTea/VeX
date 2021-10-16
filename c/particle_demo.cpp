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
        particleSystem(std::make_unique<Particle_System>()),
        particleSystem1(std::make_unique<Particle_System>()),
        particleSystem2(std::make_unique<Particle_System>()),
        particleSystem3(std::make_unique<Particle_System>())            
    {}

    void Particle_Demo::init(){
        engine->addKeybind("resetState", sf::Keyboard::Key::Backspace);
        engine->addKeybind("snapToScreenCenterToggle", sf::Keyboard::Key::O);
        engine->addKeybind("circlePauseToggle", sf::Keyboard::Key::P);
        engine->addKeybind("showCenters", sf::Keyboard::Key::L);
        engine->addKeybind("drawParticles", sf::Keyboard::Key::K);
        engine->addKeybind("nextPrimitiveType", sf::Keyboard::Key::Add);
        engine->addKeybind("prevPrimitiveType", sf::Keyboard::Key::Subtract);
        particleSystem->setPosition(sf::Mouse::getPosition());
    }

    void Particle_Demo::handleInput(){
        if(engine->getKeybind("resetState")->onKeyDown()){
            engine->settings->currentParticleCount = 0;
            engine->addState(std::make_unique<VeX::Particle_Demo>(snapToScreenCenter), true);
        }

        if(engine->getKeybind("snapToScreenCenterToggle")->onKeyDown()){
            snapToScreenCenter = !snapToScreenCenter;
        }

        if(engine->getKeybind("circlePauseToggle")->onKeyDown()){
            circlePaused = !circlePaused;
        }

        if(engine->getKeybind("showCenters")->onKeyDown()){
            showCenters = !showCenters;
        }

        if(engine->getKeybind("drawParticles")->onKeyDown()){
            drawParticles = !drawParticles;
        }

        if(engine->getKeybind("nextPrimitiveType")->onKeyDown()){
            if(primitiveTypeIndex >= primitiveTypes.size()-1){
                primitiveTypeIndex = 0;
            }else{
                primitiveTypeIndex++;
            }
            particleSystem->setPrimitiveType(primitiveTypes[primitiveTypeIndex]);
            particleSystem1->setPrimitiveType(primitiveTypes[primitiveTypeIndex]);
            particleSystem2->setPrimitiveType(primitiveTypes[primitiveTypeIndex]);
            particleSystem3->setPrimitiveType(primitiveTypes[primitiveTypeIndex]);
        }

        if(engine->getKeybind("prevPrimitiveType")->onKeyDown()){
            if(primitiveTypeIndex < 1){
                primitiveTypeIndex = primitiveTypes.size()-1;
            }else{
                primitiveTypeIndex--;
            }
            particleSystem->setPrimitiveType(primitiveTypes[primitiveTypeIndex]);
            particleSystem1->setPrimitiveType(primitiveTypes[primitiveTypeIndex]);
            particleSystem2->setPrimitiveType(primitiveTypes[primitiveTypeIndex]);
            particleSystem3->setPrimitiveType(primitiveTypes[primitiveTypeIndex]);
        }

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
            particleSystem->setPosition(getPositionOnCircle(circleCenter, 400.f, circleAngle));
            particleSystem1->setPosition(getPositionOnCircle(circleCenter, 400.f, circleAngle+90.f));
            particleSystem2->setPosition(getPositionOnCircle(circleCenter, 400.f, circleAngle+180.f));
            particleSystem3->setPosition(getPositionOnCircle(circleCenter, 400.f, circleAngle+270.f));
            circleAngle += 1.65 * 360.f * delta;
            if(circleAngle >= 360.f){
                circleAngle -= 360.f;
            }   //0.215 & 500.f highest known to inhibit effect and 0.191 smallest known
        }

        if(!maxParticleCountReached && engine->getFramerate() > 75.f && engine->settings->currentParticleCount < 40'000){
            for(unsigned int i=0; i<20; i++){
                particleSystem->addParticle(std::make_unique<Particle>(particleSystem->getPosition() + sf::Vector2f{-100 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/(100*2))),
                                                                                    -100 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/(100*2)))}, Definition::defaultParticleMotionDampening,
                                                                                    Color_Gradient({{102, 31, 196}, {21, 232, 255}, {255,255,255}}), 3500.f));
                particleSystem1->addParticle(std::make_unique<Particle>(particleSystem1->getPosition() + sf::Vector2f{-100 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/(100*2))),
                                                                                    -100 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/(100*2)))}, Definition::defaultParticleMotionDampening,
                                                                                    Color_Gradient({{102, 31, 196}, {21, 232, 255}, {255,255,255}}), 3500.f));
                particleSystem2->addParticle(std::make_unique<Particle>(particleSystem2->getPosition() + sf::Vector2f{-100 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/(100*2))),
                                                                                    -100 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/(100*2)))}, Definition::defaultParticleMotionDampening,
                                                                                    Color_Gradient({{102, 31, 196}, {21, 232, 255}, {255,255,255}}), 3500.f));
                particleSystem3->addParticle(std::make_unique<Particle>(particleSystem3->getPosition() + sf::Vector2f{-100 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/(100*2))),
                                                                                    -100 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/(100*2)))}, Definition::defaultParticleMotionDampening,
                                                                                    Color_Gradient({{102, 31, 196}, {21, 232, 255}, {255,255,255}}), 3500.f));
                engine->settings->currentParticleCount += 4;
            }
        }else if(engine->getFramerate() < 62.f){
            particleSystem->removeOldestParticle();
            particleSystem1->removeOldestParticle();
            particleSystem2->removeOldestParticle();
            particleSystem3->removeOldestParticle();
            engine->settings->currentParticleCount -= 4;
            maxParticleCountReached = true;
        }else{
            maxParticleCountReached = true;
        }

        particleSystem->update(delta);
        particleSystem1->update(delta);
        particleSystem2->update(delta);
        particleSystem3->update(delta);
    }

    void Particle_Demo::draw(float delta){
        engine->window.clear();

        if(drawParticles){
            particleSystem->draw(delta);
            particleSystem1->draw(delta);
            particleSystem2->draw(delta);
            particleSystem3->draw(delta);
        }
        
        if(showCenters){
            particleSystem->drawCenterPoint();
            particleSystem1->drawCenterPoint();
            particleSystem2->drawCenterPoint();
            particleSystem3->drawCenterPoint();
        }

        engine->displayFramerate();
        engine->displayCurrentParticleCount();
        engine->window.display();
    }

} // namespace VeX
