#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Paddle.h"
#include "Ball.h"
#include "Brick.h"

struct BlockData {
    float x, y;
    int hp;
};

class GameState {
public:
    sf::Vector2f paletkaPos;
    sf::Vector2f pilkaPos;
    sf::Vector2f pilkaVel;
    std::vector<BlockData> bloki;
    void zapisz(const Paddle&, const Ball&, const std::vector<Brick>&);
    bool zapiszDoPliku(const std::string&) const;
    bool wczytajZPliku(const std::string&);
};
