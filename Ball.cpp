#include "Ball.h"
#include <cmath> 

Ball::Ball(float pilka_x, float pilka_y)
{
    pilka_ksztalt.setRadius(10); 
    pilka_ksztalt.setFillColor(sf::Color::White); 
    pilka_ksztalt.setPosition(pilka_x, pilka_y); 
    pilka_vel = { pilka_velBazowa, -pilka_velBazowa }; 
}

void Ball::pilka_aktualizuj(float okno_szerokosc, float okno_wysokosc) {
    pilka_ksztalt.move(pilka_vel); 

    if (pilka_ksztalt.getPosition().x <= 0 || pilka_ksztalt.getPosition().x + pilka_ksztalt.getRadius() * 2 >= okno_szerokosc)
        pilka_vel.x = -pilka_vel.x; 

    if (pilka_ksztalt.getPosition().y <= 0)
        pilka_vel.y = -pilka_vel.y; 
}

void Ball::pilka_sprawdzKolizjePaletka(Paddle& paletka) { 

    if (pilka_ksztalt.getGlobalBounds().intersects(paletka.paletka_ksztalt.getGlobalBounds())) {
        pilka_vel.y = -std::abs(pilka_vel.y); 

        if (pilka_vel.x == 0) {
            float paletka_centrum = paletka.paletka_ksztalt.getPosition().x + paletka.paletka_ksztalt.getSize().x / 2.0f;
            pilka_vel.x = (pilka_ksztalt.getPosition().x < paletka_centrum) ? -pilka_velBazowa : pilka_velBazowa;
        }
    }
}

bool Ball::pilka_sprawdzKolizjeKlocek(Brick& klocek) { 

    if (pilka_ksztalt.getGlobalBounds().intersects(klocek.klocek_ksztalt.getGlobalBounds())) {
        pilka_vel.y = -pilka_vel.y; 
        return true; 
    }
    return false; 
}

void Ball::pilka_resetuj(float reset_x, float reset_y) {
    pilka_ksztalt.setPosition(reset_x, reset_y); 
    pilka_vel = { pilka_velBazowa, -pilka_velBazowa }; 
}