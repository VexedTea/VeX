#include "../h/pause_menu.hpp"

namespace VeX{

    Pause_Menu::Pause_Menu(){}

    void Pause_Menu::init(){
        engine->addGlobalKeybind(
            "ToggleMenu", 
            sf::Keyboard::Key::Escape, 
            KeybindCondition::OnKeyUp, 
            [&](){
                engine->pauseMenuOpen = !engine->pauseMenuOpen;
            }
        );
        background.setTexture(engine->loadTexture("pause_menu_background", "assets/textures/ui/pause_menu_background.png"));
        background = util::snapTo(background, {0.5, 0.5}, {0.8, 0.8});
        arrangeButtons();
    }

    void Pause_Menu::handleInput(){
        //Handle ur input
        
        sf::Event event;
        while (engine->window.pollEvent(event)){
            if (event.type == sf::Event::Closed)
            engine->window.close();
        }
    }

    void Pause_Menu::update(float delta){
        for(unsigned i=0; i<buttons.size(); i++){
            buttons[i].update(delta);
        }
    }

    void Pause_Menu::draw(float delta){
        engine->window.draw(background);
        for(unsigned i=0; i<buttons.size(); i++){
            buttons[i].draw(delta);
        }
    }

    void Pause_Menu::addStateSelection(const std::function<State_Ptr()> & makeState, const UI::Button_Data & optionData){
        UI::Button_Textures textures = {engine->loadTexture("pause_menu_background", "assets/textures/ui/pause_menu_background.png"), engine->loadTexture("pause_menu_background", "assets/textures/ui/pause_menu_background.png"), engine->loadTexture("pause_menu_background", "assets/textures/ui/pause_menu_background.png")};
        buttons.push_back(UI::Button(optionData, textures, [=](){engine->addState(makeState(), true);}));
    }

    void Pause_Menu::arrangeButtons(){
        int colCount = sqrt(buttons.size());
        int rowCount = buttons.size()/colCount;
        if(int(buttons.size()) > colCount * rowCount){
            colCount = int(colCount)+1;
        }
        int colNr{0}; int rowNr{0};
        for(unsigned i=0; i<buttons.size(); i++){
            if(rowNr >= rowCount){
                colNr++;
                rowNr=0;
            }
            sf::Vector2f newPos{0.f,0.f};
            newPos.x = 0.1 + (0.8/float(colCount)/2.f) + float(colNr) * (0.8/float(colCount));
            newPos.y = 0.1 + (0.8/float(rowCount)/2.f) + float(rowNr) * (0.8/float(rowCount));
            buttons[i].snapTo(newPos, sf::Vector2f(0.8/float(colCount), 0.8/float(rowCount)));
            rowNr++;
        }
    }

} // namespace VeX
