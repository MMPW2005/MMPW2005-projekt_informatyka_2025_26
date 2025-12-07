#pragma once
#include <SFML/Graphics.hpp>

class Paddle {
public:
    sf::RectangleShape paletka_ksztalt; 
    Paddle(float paletka_x, float paletka_y); 
    void paletka_aktualizuj(float okno_szerokosc);

private:
    float paletka_vel = 8; 
};