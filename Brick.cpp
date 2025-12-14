#include "Brick.h"

Brick::Brick(float x, float y, float w, float h, int hp) {
    klocek_hp = hp;
    klocek_ksztalt.setSize({ w, h });
    klocek_ksztalt.setPosition(x, y);

    if (hp == 3) {
        klocek_ksztalt.setFillColor(sf::Color::Red);
    }
    else if (hp == 2) {
        klocek_ksztalt.setFillColor(sf::Color::Yellow);
    }
    else {
        klocek_ksztalt.setFillColor(sf::Color::Green);
    }
}

bool Brick::klocek_jestZniszczony() const {
    return klocek_hp <= 0;
}

void Brick::klocek_uderzenie() {
    klocek_hp--;
    if (klocek_hp == 2) {
        klocek_ksztalt.setFillColor(sf::Color::Yellow);
    }
    else if (klocek_hp == 1) {
        klocek_ksztalt.setFillColor(sf::Color::Green);
    }
}
