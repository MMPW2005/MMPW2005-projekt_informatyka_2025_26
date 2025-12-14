#include "Paddle.h"

Paddle::Paddle(float x, float y) {
    paletka_ksztalt.setSize({ 120, 20 });
    paletka_ksztalt.setFillColor(sf::Color::White);
    paletka_ksztalt.setPosition(x, y);
}

void Paddle::paletka_aktualizuj(float okno_szer) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && paletka_ksztalt.getPosition().x > 0) {
        paletka_ksztalt.move(-paletka_vel, 0);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && paletka_ksztalt.getPosition().x + paletka_ksztalt.getSize().x < okno_szer) {
        paletka_ksztalt.move(paletka_vel, 0);
    }
}
