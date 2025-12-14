#include "GameUI.h"

void GameUI::init() {
    font.loadFromFile("arial.ttf");
    tekst.setFont(font);
    tekst.setCharacterSize(40);
    
    std::string opcje[3] = { "Nowa gra - N", "Wczytaj - L", "Wyjscie - ESC" };
    for (int i = 0; i < 3; i++) {
        menuOpcje[i].setFont(font);
        menuOpcje[i].setCharacterSize(30);
        menuOpcje[i].setString(opcje[i]);
        menuOpcje[i].setPosition(200.f, 200.f + i * 50.f);
    }

    std::string pOpcje[4] = { "Restart - R", "Wczytaj - L", "Zapisz - S", "Wznow - P" };
    for (int i = 0;i < 4;i++) {
        pauseOpcje[i].setFont(font);
        pauseOpcje[i].setCharacterSize(30);
        pauseOpcje[i].setString(pOpcje[i]);
        pauseOpcje[i].setPosition(300.f, 250.f + i * 40.f);
    }
}

void GameUI::draw(sf::RenderWindow& w, StanGry s) {
    if (s == StanGry::PAUZA) {
        drawPauseMenu(w);
    }
    else if (s == StanGry::WYGRANA) {
        tekst.setString("WYGRANA! R");
        tekst.setPosition(250.f, 300.f);
        w.draw(tekst);
    }
    else if (s == StanGry::PRZEGRANA) {
        tekst.setString("PRZEGRANA! R");
        tekst.setPosition(250.f, 300.f);
        w.draw(tekst);
    }
}

void GameUI::drawMenu(sf::RenderWindow& w) {
    sf::Text tytul;
    tytul.setFont(font);
    tytul.setCharacterSize(50);
    tytul.setString("ARKANOID");
    tytul.setPosition(180.f, 100.f);
    w.draw(tytul);
    for (int i = 0;i < 3;i++) {
        w.draw(menuOpcje[i]);
    }
}

void GameUI::drawPauseMenu(sf::RenderWindow& w) {
    tekst.setString("PAUZA");
    tekst.setPosition(300.f, 200.f);
    w.draw(tekst);
    for (int i = 0;i < 4;i++) {
        w.draw(pauseOpcje[i]);
    }
}
