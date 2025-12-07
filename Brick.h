#pragma once
#include <SFML/Graphics.hpp>

class Brick {
public:
    sf::RectangleShape klocek_ksztalt; 
    int klocek_hp; 

    Brick(float klocek_x, float klocek_y, float klocek_szerokosc, float klocek_wysokosc, int klocek_hp_val);

    bool klocek_jestZniszczony() const; 
    void klocek_uderzenie(); 
};