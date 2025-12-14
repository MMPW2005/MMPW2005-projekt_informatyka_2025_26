#pragma once
#include <SFML/Graphics.hpp>
#include "Paddle.h"
#include "Brick.h"

class Ball {
public:
    sf::CircleShape pilka_ksztalt;
    Ball(float x, float y);
    void pilka_aktualizuj(float okno_szer, float okno_wys);
    void pilka_sprawdzKolizjePaletka(Paddle& paletka);
    bool pilka_sprawdzKolizjeKlocek(Brick& klocek);
    void pilka_resetuj(float x, float y);
    sf::Vector2f pilka_pobierzVel() const { return pilka_vel; }
    void pilka_ustawVel(sf::Vector2f v) { pilka_vel = v; }
private:
    sf::Vector2f pilka_vel;
    float pilka_velBazowa = 5.f;
};
