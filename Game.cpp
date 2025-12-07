#include "Game.h" 
#include <iostream> 

Game::Game()
    : okno_render(sf::VideoMode(OKNO_SZEROKOSC, OKNO_WYSOKOSC), "Arkanoid") , paletka_obiekt(static_cast<float>(OKNO_SZEROKOSC) / 2 - 60, static_cast<float>(OKNO_WYSOKOSC) - 40) , pilka_obiekt(static_cast<float>(OKNO_SZEROKOSC) / 2, static_cast<float>(OKNO_WYSOKOSC) / 2) {
    gra_stan = StanGry::GRA_W_TRAKCIE; 
    okno_render.setFramerateLimit(60);

    if (!ui_czcionka.loadFromFile("arial.ttf")) {} 

    ui_centrowanieTekstu(ui_tekstPauza, "PAUZA", 80, sf::Color::White, static_cast<float>(OKNO_WYSOKOSC) / 2.0f);
    ui_centrowanieTekstu(ui_tekstMenu, "Wcisnij L - Wczytaj | S - Zapisz | P - Kontynuuj | R - Restartuj", 20, sf::Color::Yellow, static_cast<float>(OKNO_WYSOKOSC) / 2.0f + 50);
    ui_tekstKoniecGry.setFont(ui_czcionka); 
    ui_tekstKoniecGry.setCharacterSize(40);
    gra_resetujKlocki(); 
}

void Game::gra_uruchom() {
    while (okno_render.isOpen()) { 
        gra_przetwarzajZdarzenia(); 
        gra_aktualizuj(); 
        gra_rysuj(); 
    }
}

void Game::gra_przetwarzajZdarzenia() {
    sf::Event zdarzenie;
    while (okno_render.pollEvent(zdarzenie)) { 
        if (zdarzenie.type == sf::Event::Closed)
            okno_render.close(); 

        if (zdarzenie.type == sf::Event::KeyPressed && zdarzenie.key.code == sf::Keyboard::P) {
            if (gra_stan == StanGry::GRA_W_TRAKCIE)
                gra_stan = StanGry::GRA_ZAPAUZOWANA; 
            else if (gra_stan == StanGry::GRA_ZAPAUZOWANA)
                gra_stan = StanGry::GRA_W_TRAKCIE;
        }

        bool mozna_restartowac = (gra_stan != StanGry::GRA_W_TRAKCIE);
        if (zdarzenie.type == sf::Event::KeyPressed && zdarzenie.key.code == sf::Keyboard::R && mozna_restartowac) {
            gra_resetujKlocki(); 
            pilka_obiekt.pilka_resetuj(static_cast<float>(OKNO_SZEROKOSC) / 2, static_cast<float>(OKNO_WYSOKOSC) / 2);
            paletka_obiekt.paletka_ksztalt.setPosition(static_cast<float>(OKNO_SZEROKOSC) / 2 - 60, static_cast<float>(OKNO_WYSOKOSC) - 40);
            gra_stan = StanGry::GRA_W_TRAKCIE; 
        }

        if (gra_stan == StanGry::GRA_ZAPAUZOWANA) {

            if (zdarzenie.type == sf::Event::KeyPressed && zdarzenie.key.code == sf::Keyboard::S) {
                stan_ostatni.stan_zapisz(paletka_obiekt, pilka_obiekt, klocki_lista); 
                if (stan_ostatni.stan_zapiszDoPliku("savegame.bin")) 
                    std::cout << "Zapisano stan gry.\n";
            }

            if (zdarzenie.type == sf::Event::KeyPressed && zdarzenie.key.code == sf::Keyboard::L) {
                if (stan_ostatni.stan_wczytajZPliku("savegame.bin")) { 
                    stan_przywroc(); 
                    std::cout << "Wczytano stan gry.\n";
                    gra_stan = StanGry::GRA_W_TRAKCIE; 
                }
                else {
                    std::cout << "Blad: Nie udalo sie wczytac stanu gry (brak pliku?)\n";
                }
            }
        }
    }
}

void Game::ui_centrowanieTekstu(sf::Text& tekst, const std::string& tresc, int rozmiar, sf::Color kolor, float pozycja_y) {
    tekst.setFont(ui_czcionka);
    tekst.setString(tresc);
    tekst.setCharacterSize(rozmiar);
    tekst.setFillColor(kolor);
    sf::FloatRect granice = tekst.getLocalBounds();
    tekst.setOrigin(granice.left + granice.width / 2.0f, granice.top + granice.height / 2.0f);
    tekst.setPosition(static_cast<float>(OKNO_SZEROKOSC) / 2.0f, pozycja_y);
}

void Game::stan_przywroc() {
    paletka_obiekt.paletka_ksztalt.setPosition(stan_ostatni.stan_paletkaPos);
    pilka_obiekt.pilka_ksztalt.setPosition(stan_ostatni.stan_pilkaPos);
    pilka_obiekt.pilka_ustawVel(stan_ostatni.stan_pilkaVel);

    klocki_lista.clear(); 

    float klocek_w = 100;
    float klocek_h = 30;

    for (const auto& blok_dane : stan_ostatni.stan_bloki) {
        Brick nowy_klocek(blok_dane.blok_pozycjaX, blok_dane.blok_pozycjaY, klocek_w, klocek_h, blok_dane.blok_hp);

        if (nowy_klocek.klocek_hp == 3) {
            nowy_klocek.klocek_ksztalt.setFillColor(sf::Color::Red);
        }
        else if (nowy_klocek.klocek_hp == 2) {
            nowy_klocek.klocek_ksztalt.setFillColor(sf::Color::Yellow);
        }
        else if (nowy_klocek.klocek_hp == 1) {
            nowy_klocek.klocek_ksztalt.setFillColor(sf::Color::Green);
        }
        else {
            nowy_klocek.klocek_ksztalt.setFillColor(sf::Color::Black);
        }
        klocki_lista.push_back(std::move(nowy_klocek)); 
    }
}

void Game::gra_sprawdzStatus() {
    if (pilka_obiekt.pilka_ksztalt.getPosition().y > OKNO_WYSOKOSC) {
        gra_stan = StanGry::GRA_KONIEC_PRZEGRANA;
        ui_tekstKoniecGry.setString("PRZEGRANA! Wcisnij R.");
        ui_tekstKoniecGry.setFillColor(sf::Color::Red);
    }

    bool wszyscy_zniszczeni = true;
    for (const auto& klocek : klocki_lista) {
        if (!klocek.klocek_jestZniszczony()) {
            wszyscy_zniszczeni = false; 
            break;
        }
    }
    if (wszyscy_zniszczeni) {
        gra_stan = StanGry::GRA_KONIEC_WYGRANA;
        ui_tekstKoniecGry.setString("WYGRANA! Wcisnij R.");
        ui_tekstKoniecGry.setFillColor(sf::Color::Green);
    }

    if (gra_stan == StanGry::GRA_KONIEC_PRZEGRANA || gra_stan == StanGry::GRA_KONIEC_WYGRANA) {
        sf::FloatRect granice = ui_tekstKoniecGry.getLocalBounds();
        ui_tekstKoniecGry.setOrigin(granice.left + granice.width / 2.0f, granice.top + granice.height / 2.0f);
        ui_tekstKoniecGry.setPosition(static_cast<float>(OKNO_SZEROKOSC) / 2.0f, static_cast<float>(OKNO_WYSOKOSC) / 2.0f);
    }
}


void Game::gra_aktualizuj() {
    if (gra_stan != StanGry::GRA_W_TRAKCIE)
        return; 

    paletka_obiekt.paletka_aktualizuj(static_cast<float>(OKNO_SZEROKOSC));
    pilka_obiekt.pilka_aktualizuj(static_cast<float>(OKNO_SZEROKOSC), static_cast<float>(OKNO_WYSOKOSC));
    pilka_obiekt.pilka_sprawdzKolizjePaletka(paletka_obiekt);
    gra_sprawdzStatus();

    for (auto& klocek : klocki_lista) {
        if (!klocek.klocek_jestZniszczony() && pilka_obiekt.pilka_sprawdzKolizjeKlocek(klocek))
            klocek.klocek_uderzenie(); 
    }
}

void Game::gra_rysuj() {
    okno_render.clear(sf::Color::Black); 
    okno_render.draw(paletka_obiekt.paletka_ksztalt);
    okno_render.draw(pilka_obiekt.pilka_ksztalt);

    for (auto& klocek : klocki_lista)
        if (!klocek.klocek_jestZniszczony())
            okno_render.draw(klocek.klocek_ksztalt);

    if (gra_stan != StanGry::GRA_W_TRAKCIE) {
        sf::RectangleShape nakladka({ static_cast<float>(OKNO_SZEROKOSC), static_cast<float>(OKNO_WYSOKOSC) });
        nakladka.setFillColor(sf::Color(0, 0, 0, 150)); 
        okno_render.draw(nakladka);
        if (gra_stan == StanGry::GRA_ZAPAUZOWANA) {
            okno_render.draw(ui_tekstPauza);
            okno_render.draw(ui_tekstMenu);
        }
        else if (gra_stan == StanGry::GRA_KONIEC_PRZEGRANA || gra_stan == StanGry::GRA_KONIEC_WYGRANA) {
            okno_render.draw(ui_tekstKoniecGry);
        }
    }
    okno_render.display(); 
}

void Game::gra_resetujKlocki() {
    klocki_lista.clear(); 
    float klocek_w = 100;
    float klocek_h = 30;

    const float MARGINES_X_START = 125;

    for (int rzad_idx = 0; rzad_idx < 3; rzad_idx++) {
        for (int kolumna_idx = 0; kolumna_idx < 5; kolumna_idx++) {
            klocki_lista.emplace_back(
                MARGINES_X_START + kolumna_idx * (klocek_w + 15),
                rzad_idx * (klocek_h + 20) + 50,
                klocek_w,
                klocek_h,
                3 - rzad_idx 
            );
        }
    }
}