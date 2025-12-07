#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Paddle.h"
#include "Ball.h"
#include "Brick.h"

struct BlockData
{
    float blok_pozycjaX, blok_pozycjaY; 
    int blok_hp; 
};

class GameState
{
public:
    GameState(); 

    void stan_zapisz(const Paddle& paletka,
        const Ball& pilka,
        const std::vector<Brick>& klocki);

    bool stan_zapiszDoPliku(const std::string& nazwa_pliku) const; 
    bool stan_wczytajZPliku(const std::string& nazwa_pliku); 

    sf::Vector2f stan_paletkaPos;
    sf::Vector2f stan_pilkaPos; 
    sf::Vector2f stan_pilkaVel; 
    std::vector<BlockData> stan_bloki; 
};