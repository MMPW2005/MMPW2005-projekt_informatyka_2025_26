#include "Ball.h"
#include <cmath>

Ball::Ball(float x, float y) {
    pilka_ksztalt.setRadius(10);
    pilka_ksztalt.setFillColor(sf::Color::White);
    pilka_ksztalt.setPosition(x, y);
    pilka_vel = { pilka_velBazowa, -pilka_velBazowa };
}

void Ball::pilka_aktualizuj(float okno_szer, float okno_wys) {
    pilka_ksztalt.move(pilka_vel);

    if (pilka_ksztalt.getPosition().x <= 0 || pilka_ksztalt.getPosition().x + 20 >= okno_szer) {
        pilka_vel.x = -pilka_vel.x;
    }

    if (pilka_ksztalt.getPosition().y <= 0) {
        pilka_vel.y = -pilka_vel.y;
    }
}

void Ball::pilka_sprawdzKolizjePaletka(Paddle& paletka) {
    if (pilka_ksztalt.getGlobalBounds().intersects(paletka.paletka_ksztalt.getGlobalBounds())) {
        pilka_vel.y = -std::abs(pilka_vel.y);
    }
}

bool Ball::pilka_sprawdzKolizjeKlocek(Brick& klocek) {
    if (pilka_ksztalt.getGlobalBounds().intersects(klocek.klocek_ksztalt.getGlobalBounds())) {
        pilka_vel.y = -pilka_vel.y;
        return true;
    }
    return false;
}

void Ball::pilka_resetuj(float x, float y) {
    pilka_ksztalt.setPosition(x, y);
    pilka_vel = { pilka_velBazowa, -pilka_velBazowa };
}
