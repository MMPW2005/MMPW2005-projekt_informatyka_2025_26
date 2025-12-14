#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Paddle.h"
#include "Ball.h"
#include "Brick.h"
#include "GameLogic.h"
#include "GameUI.h"
#include "GameState.h"

class Game {
public:
    Game();
    void run();
private:
    sf::RenderWindow okno;
    Paddle paletka;
    Ball pilka;
    std::vector<Brick> klocki;
    GameUI ui;
    GameState zapis;
    StanGry stan;
    void events();
    void update();
    void draw();
};
