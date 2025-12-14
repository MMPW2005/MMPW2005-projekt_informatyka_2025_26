#pragma once
#include <SFML/Graphics.hpp>

class Paddle {
public:
    sf::RectangleShape paletka_ksztalt;
    Paddle(float x, float y);
    void paletka_aktualizuj(float okno_szer);
private:
    float paletka_vel = 8.f;
};
