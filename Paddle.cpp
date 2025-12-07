#include "Paddle.h"

Paddle::Paddle(float paletka_x, float paletka_y) {
    paletka_ksztalt.setSize({ 120, 20 }); 
    paletka_ksztalt.setFillColor(sf::Color::White);
    paletka_ksztalt.setPosition(paletka_x, paletka_y); 
}

void Paddle::paletka_aktualizuj(float okno_szerokosc) {

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && paletka_ksztalt.getPosition().x > 0)
        paletka_ksztalt.move(-paletka_vel, 0);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && paletka_ksztalt.getPosition().x + paletka_ksztalt.getSize().x < okno_szerokosc)
        paletka_ksztalt.move(paletka_vel, 0);
}