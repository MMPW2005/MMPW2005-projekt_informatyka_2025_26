#include "GameLogic.h"

void GameLogic::resetujKlocki(std::vector<Brick>& k) {
    k.clear();
    for (int r = 0; r < 3; r++) {
        for (int c = 0; c < 5; c++) {
            k.emplace_back(125 + c * 115, 50 + r * 50, 100, 30, 3 - r);
        }
    }
}

void GameLogic::aktualizuj(Paddle& p, Ball& b, std::vector<Brick>& k, StanGry& s, int h) {
    b.pilka_sprawdzKolizjePaletka(p);
    for (auto& klocek : k) {
        if (!klocek.klocek_jestZniszczony() && b.pilka_sprawdzKolizjeKlocek(klocek)) {
            klocek.klocek_uderzenie();
        }
    }
    if (b.pilka_ksztalt.getPosition().y > h) {
        s = StanGry::PRZEGRANA;
    }

    bool win = true;
    for (auto& klocek : k) {
        if (!klocek.klocek_jestZniszczony()) {
            win = false;
        }
    }
    if (win) {
        s = StanGry::WYGRANA;
    }
}

void GameLogic::przywroc(Paddle& p, Ball& b, std::vector<Brick>& k, const GameState& s) {
    p.paletka_ksztalt.setPosition(s.paletkaPos);
    b.pilka_ksztalt.setPosition(s.pilkaPos);
    b.pilka_ustawVel(s.pilkaVel);
    k.clear();
    for (auto& d : s.bloki) {
        k.emplace_back(d.x, d.y, 100, 30, d.hp);
    }
}
