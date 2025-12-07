#pragma once
#include <SFML/Graphics.hpp> /
#include "Paddle.h"          
#include "Brick.h"           

class Ball {
public:
    sf::CircleShape pilka_ksztalt; 
    Ball(float pilka_x, float pilka_y); 

    void pilka_aktualizuj(float okno_szerokosc, float okno_wysokosc);
    void pilka_sprawdzKolizjePaletka(Paddle& paletka);
    bool pilka_sprawdzKolizjeKlocek(Brick& klocek);
    void pilka_resetuj(float reset_x, float reset_y); 
    sf::Vector2f pilka_pobierzVel() const { return pilka_vel; }
    void pilka_ustawVel(sf::Vector2f nowa_vel) { pilka_vel = nowa_vel; }

private:
    sf::Vector2f pilka_vel; 
    float pilka_velBazowa = 5; 
};