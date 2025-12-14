#pragma once
#include <SFML/Graphics.hpp>
#include "GameLogic.h"

class GameUI {
public:
    void init();
    void draw(sf::RenderWindow&, StanGry);
    void drawMenu(sf::RenderWindow&);
    void drawPauseMenu(sf::RenderWindow&);
private:
    sf::Font font;
    sf::Text tekst;
    sf::Text menuOpcje[3];
    sf::Text pauseOpcje[4];
};
