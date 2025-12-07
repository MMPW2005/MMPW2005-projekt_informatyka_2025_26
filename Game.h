#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Paddle.h"
#include "Ball.h"
#include "Brick.h"
#include "GameState.h"

enum class StanGry {
    GRA_W_TRAKCIE,
    GRA_ZAPAUZOWANA,
    GRA_KONIEC_PRZEGRANA,
    GRA_KONIEC_WYGRANA
};

class Game {
public:
    Game(); 
    void gra_uruchom(); 

private:
    const int OKNO_SZEROKOSC = 800; 
    const int OKNO_WYSOKOSC = 600;  

    sf::RenderWindow okno_render; 
    Paddle paletka_obiekt; 
    Ball pilka_obiekt; 
    std::vector<Brick> klocki_lista; 
    sf::Font ui_czcionka; 
    sf::Text ui_tekstPauza; 
    sf::Text ui_tekstMenu; 
    sf::Text ui_tekstKoniecGry; 

    StanGry gra_stan; 
    GameState stan_ostatni; 

    void gra_przetwarzajZdarzenia(); 
    void gra_aktualizuj();
    void gra_rysuj(); 
    void ui_centrowanieTekstu(sf::Text& tekst, const std::string& tresc, int rozmiar, sf::Color kolor, float pozycja_y);
    void gra_sprawdzStatus(); 
    void gra_resetujKlocki(); 
    void stan_przywroc(); 
};