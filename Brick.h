#pragma once
#include <SFML/Graphics.hpp>

class Brick {
public:
    sf::RectangleShape klocek_ksztalt;
    int klocek_hp;
    Brick(float x, float y, float w, float h, int hp);
    bool klocek_jestZniszczony() const;
    void klocek_uderzenie();
};
