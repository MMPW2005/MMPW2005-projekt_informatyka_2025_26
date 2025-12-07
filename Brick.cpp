#include "Brick.h"

Brick::Brick(float klocek_x, float klocek_y, float klocek_szerokosc, float klocek_wysokosc, int klocek_hp_val) {
    klocek_hp = klocek_hp_val; 
    klocek_ksztalt.setSize({ klocek_szerokosc, klocek_wysokosc }); 
    klocek_ksztalt.setPosition(klocek_x, klocek_y); 
   
    if (klocek_hp == 3) {
        klocek_ksztalt.setFillColor(sf::Color::Red);
    }
    else if (klocek_hp == 2) {
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