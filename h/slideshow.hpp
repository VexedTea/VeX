#ifndef __SLIDESHOW_HPP__
#define __SLIDESHOW_HPP__

#include "SFML/Graphics.hpp"

#include <string>
#include <vector>
#include <memory>
#include <stdlib.h>
#include <thread>
#include <mutex>
#include <functional>

#include "particle_image.hpp"
#include "loading_state.hpp"

namespace VeX{
    struct Slide_Transition{
        std::function<bool()> activator;
        sf::Vector2f offToPos;
        sf::Vector2f inFromPos;
    };

    class Slideshow : public State{
    private:
        std::string folderPath;
        std::vector<std::unique_ptr<Particle_Image>> images;
        unsigned int activeImageIndex;
        unsigned int prevImageIndex;
        std::vector<Slide_Transition> slideTransitions;

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

        std::vector<std::string> loadImages(){
            float progress = 0.f;
            std::mutex progressMutex;
            std::vector<std::string> textureNames;
            engine->runPocketState(std::make_unique<Loading_State>("Loading Images", progress, progressMutex, 
                [this, &textureNames, &progress, &progressMutex](){
                    engine->loadTexturesFromFolder(textureNames, folderPath, progress, progressMutex);
                }
            ));
            return textureNames;
        }

        void handleSlideChanges(){
            for(Slide_Transition slideTransition : slideTransitions){
                if(slideTransition.activator()){
                    images[activeImageIndex]->collapseTo(slideTransition.offToPos);
                    images[prevImageIndex]->stop();
                    images[prevImageIndex]->setParticles();
                    images[prevImageIndex]->setSize({float(engine->settings->screenWidth),float(engine->settings->screenHeight)});
                    images[prevImageIndex]->setCenterPosition(sf::Vector2f(engine->settings->screenWidth/2.f, engine->settings->screenHeight/2.f));
                    prevImageIndex = activeImageIndex;
                    newRandIndex();
                    images[activeImageIndex]->comeInFrom(slideTransition.inFromPos);
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
            std::vector<std::string> textureNames = loadImages();
            std::cout << textureNames[0] << std::endl;

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

            float screenWidth = engine->settings->screenWidth;
            float screenHeight = engine->settings->screenHeight;
            slideTransitions.push_back(Slide_Transition{[]()bool{return engine->getKeybind("nextUp")->onKeyDown();}, sf::Vector2f(screenWidth/2.f, 0.f-(screenHeight/10.f)), sf::Vector2f(screenWidth/2.f, screenHeight*1.1)});
            slideTransitions.push_back(Slide_Transition{[]()bool{return engine->getKeybind("nextLeft")->onKeyDown();}, sf::Vector2f(0.f-(screenWidth/10.f), screenHeight/2.f), sf::Vector2f(screenWidth*1.1, screenHeight/2.f)});
            slideTransitions.push_back(Slide_Transition{[]()bool{return engine->getKeybind("nextDown")->onKeyDown();}, sf::Vector2f(screenWidth/2.f, screenHeight*1.1), sf::Vector2f(screenWidth/2.f, 0.f-(screenHeight/10.f))});
            slideTransitions.push_back(Slide_Transition{[]()bool{return engine->getKeybind("nextRight")->onKeyDown();}, sf::Vector2f(screenWidth*1.1, screenHeight/2.f), sf::Vector2f(0.f-(screenWidth/10.f), screenHeight/2.f)});
        }
        
        void handleInput(){

            handleSlideChanges();
            
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