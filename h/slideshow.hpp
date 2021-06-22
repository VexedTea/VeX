#ifndef __SLIDESHOW_HPP__
#define __SLIDESHOW_HPP__

#include <string>
#include <vector>
#include <memory>
#include <stdlib.h>

#include "particle_image.hpp"

namespace VeX{

    class Slideshow : public State{
    private:
        std::string folderPath;
        std::vector<std::unique_ptr<Particle_Image>> images;
        unsigned int activeImageIndex;
        unsigned int prevImageIndex;

        void newRandIndex(unsigned int depth=0){
            unsigned int newIndex = rand() % images.size();
            if(newIndex != activeImageIndex){
                activeImageIndex = newIndex;
            }else{
                if(depth<10){
                    newRandIndex(depth++);
                }else{
                    std::cout << "[VeX WARNING] newRandIndex() reached depth 10, returning." << std::endl; //TODO: add engine ostreams for warning, error, info, etc. So we dont have to use cout and change the destination in one place.
                }
            }
        }
    public:
        Slideshow(const std::string & folderPath):
            folderPath{folderPath},
            images(),
            activeImageIndex(0),
            prevImageIndex(0)
        {}
        
        void init(){
            std::vector<std::string> textureNames = engine->loadTexturesFromFolder(folderPath);
            unsigned int particleCountPerImage = engine->settings->maxParticleCount*0.5;
            for(std::string textureName : textureNames){
                images.push_back(std::move(std::make_unique<Particle_Image>(
                    engine->getTexture(textureName), particleCountPerImage, engine->settings->defaultParticleMotionDampening*15.f
                )));
                images.back()->setSize({float(engine->settings->screenWidth),float(engine->settings->screenHeight)});
                images.back()->setCenterPosition(sf::Vector2f(engine->settings->screenWidth/2.f, engine->settings->screenHeight/2.f));
            }
            engine->settings->currentParticleCount += particleCountPerImage*2;
            newRandIndex();

            images[prevImageIndex]->stop();
            images[prevImageIndex]->hide();
            images[activeImageIndex]->comeInFrom(sf::Vector2f(double(engine->settings->screenWidth)*1.1, double(engine->settings->screenHeight)/2.f));

            engine->addKeybind("nextUp", sf::Keyboard::Key::Up);
            engine->addKeybind("nextLeft", sf::Keyboard::Key::Left);
            engine->addKeybind("nextDown", sf::Keyboard::Key::Down);
            engine->addKeybind("nextRight", sf::Keyboard::Key::Right);
        }
        
        void handleInput(){
            if(engine->getKeybind("nextUp")->onKeyDown()){
                images[activeImageIndex]->collapseTo(sf::Vector2f(double(engine->settings->screenWidth)/2.f, 0.f-(engine->settings->screenHeight/10.f)));
                images[prevImageIndex]->stop();
                images[prevImageIndex]->setParticles();
                images[prevImageIndex]->setSize({float(engine->settings->screenWidth),float(engine->settings->screenHeight)});
                images[prevImageIndex]->setCenterPosition(sf::Vector2f(engine->settings->screenWidth/2.f, engine->settings->screenHeight/2.f));
                prevImageIndex = activeImageIndex;
                newRandIndex();
                images[activeImageIndex]->comeInFrom(sf::Vector2f(double(engine->settings->screenWidth)/2.f, double(engine->settings->screenHeight)*1.1));
                
            }else if(engine->getKeybind("nextLeft")->onKeyDown()){
                images[activeImageIndex]->collapseTo(sf::Vector2f(0.f-(engine->settings->screenWidth/10.f), double(engine->settings->screenHeight)/2.f));
                images[prevImageIndex]->stop();
                images[prevImageIndex]->setParticles();
                images[prevImageIndex]->setSize({float(engine->settings->screenWidth),float(engine->settings->screenHeight)});
                images[prevImageIndex]->setCenterPosition(sf::Vector2f(engine->settings->screenWidth/2.f, engine->settings->screenHeight/2.f));
                prevImageIndex = activeImageIndex;
                newRandIndex();
                images[activeImageIndex]->comeInFrom(sf::Vector2f(double(engine->settings->screenWidth)*1.1, double(engine->settings->screenHeight)/2.f));
                
            }else if(engine->getKeybind("nextDown")->onKeyDown()){
                images[activeImageIndex]->collapseTo(sf::Vector2f(double(engine->settings->screenWidth)/2.f, double(engine->settings->screenHeight)*1.1));
                images[prevImageIndex]->stop();
                images[prevImageIndex]->setParticles();
                images[prevImageIndex]->setSize({float(engine->settings->screenWidth),float(engine->settings->screenHeight)});
                images[prevImageIndex]->setCenterPosition(sf::Vector2f(engine->settings->screenWidth/2.f, engine->settings->screenHeight/2.f));
                prevImageIndex = activeImageIndex;
                newRandIndex();
                images[activeImageIndex]->comeInFrom(sf::Vector2f(double(engine->settings->screenWidth)/2.f, 0.f-(engine->settings->screenHeight/10.f)));
                
            }else if(engine->getKeybind("nextRight")->onKeyDown()){
                images[activeImageIndex]->collapseTo(sf::Vector2f(double(engine->settings->screenWidth)*1.1, double(engine->settings->screenHeight)/2.f));
                images[prevImageIndex]->stop();
                images[prevImageIndex]->setParticles();
                images[prevImageIndex]->setSize({float(engine->settings->screenWidth),float(engine->settings->screenHeight)});
                images[prevImageIndex]->setCenterPosition(sf::Vector2f(engine->settings->screenWidth/2.f, engine->settings->screenHeight/2.f));
                prevImageIndex = activeImageIndex;
                newRandIndex();
                images[activeImageIndex]->comeInFrom(sf::Vector2f(0.f-(engine->settings->screenWidth/10.f), double(engine->settings->screenHeight)/2.f));
                
            }
            
            sf::Event event;
            while (engine->window.pollEvent(event)){
                if (event.type == sf::Event::Closed)
                engine->window.close();
            }
        }
        
        void update(float delta){
            images[prevImageIndex]->update(delta);
            images[activeImageIndex]->update(delta);
        }
        
        void draw(float delta){
            engine->window.clear();

            images[prevImageIndex]->draw(delta);
            images[activeImageIndex]->draw(delta);
            
            engine->window.display();
        }
    };

} // namespace VeX

#endif // __SLIDESHOW_HPP__