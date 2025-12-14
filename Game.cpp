#include "Game.h"

Game::Game()
    : okno({ 800,600 }, "Arkanoid"),
    paletka(340, 560),
    pilka(400, 300),
    stan(StanGry::MENU) {
    okno.setFramerateLimit(60);
    ui.init();
    GameLogic::resetujKlocki(klocki);
}

void Game::run() {
    while (okno.isOpen()) {
        events();
        update();
        draw();
    }
}

void Game::events() {
    sf::Event e;
    while (okno.pollEvent(e)) {
        if (e.type == sf::Event::Closed) {
            okno.close();
        }
        if (e.type == sf::Event::KeyPressed) {
            if (stan == StanGry::MENU) {
                if (e.key.code == sf::Keyboard::Escape) {
                    okno.close();
                }
                if (e.key.code == sf::Keyboard::N) {
                    GameLogic::resetujKlocki(klocki);
                    pilka.pilka_resetuj(400, 300);
                    stan = StanGry::GRA;
                }
                if (e.key.code == sf::Keyboard::L) {
                    if (zapis.wczytajZPliku("save.bin")) {
                        GameLogic::przywroc(paletka, pilka, klocki, zapis);
                        stan = StanGry::GRA;
                    }
                }
            }
            if (stan == StanGry::GRA && e.key.code == sf::Keyboard::P) {
                stan = StanGry::PAUZA;
            }
            else if (stan == StanGry::PAUZA && e.key.code == sf::Keyboard::P) {
                stan = StanGry::GRA;
            }
            if (e.key.code == sf::Keyboard::R) {
                GameLogic::resetujKlocki(klocki);
                pilka.pilka_resetuj(400, 300);
                stan = StanGry::GRA;
            }
            if (stan == StanGry::PAUZA) {
                if (e.key.code == sf::Keyboard::S) {
                    zapis.zapisz(paletka, pilka, klocki);
                    zapis.zapiszDoPliku("save.bin");
                }
                if (e.key.code == sf::Keyboard::L) {
                    if (zapis.wczytajZPliku("save.bin")) {
                        GameLogic::przywroc(paletka, pilka, klocki, zapis);
                        stan = StanGry::GRA;
                    }
                }
            }
        }
    }
}

void Game::update() {
    if (stan != StanGry::GRA) {
        return;
    }
    paletka.paletka_aktualizuj(800);
    pilka.pilka_aktualizuj(800, 600);
    GameLogic::aktualizuj(paletka, pilka, klocki, stan, 600);
}

void Game::draw() {
    okno.clear();
    if (stan == StanGry::MENU) {
        ui.drawMenu(okno);
    }
    else {
        okno.draw(paletka.paletka_ksztalt);
        okno.draw(pilka.pilka_ksztalt);
        for (auto& k : klocki) {
            if (!k.klocek_jestZniszczony()) {
                okno.draw(k.klocek_ksztalt);
            }
        }
        ui.draw(okno, stan);
    }
    okno.display();
}
