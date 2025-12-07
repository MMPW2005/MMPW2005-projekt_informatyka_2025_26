#include "GameState.h"
#include <fstream> 
#include <iostream>

GameState::GameState() {} 

void GameState::stan_zapisz(const Paddle& paletka,
    const Ball& pilka,
    const std::vector<Brick>& klocki) {

    stan_paletkaPos = paletka.paletka_ksztalt.getPosition();
    stan_pilkaPos = pilka.pilka_ksztalt.getPosition();
    stan_pilkaVel = pilka.pilka_pobierzVel();

    stan_bloki.clear(); 
    stan_bloki.reserve(klocki.size()); 

    for (const auto& klocek : klocki) {
        BlockData blok_dane;
        blok_dane.blok_pozycjaX = klocek.klocek_ksztalt.getPosition().x;
        blok_dane.blok_pozycjaY = klocek.klocek_ksztalt.getPosition().y;
        blok_dane.blok_hp = klocek.klocek_hp;
        stan_bloki.push_back(blok_dane);
    }
}

bool GameState::stan_zapiszDoPliku(const std::string& nazwa_pliku) const {
    std::ofstream ofs(nazwa_pliku, std::ios::binary);
    if (!ofs.is_open()) {
        std::cerr << "Blad: Nie mozna otworzyc pliku do zapisu!\n";
        return false;
    }

    ofs.write((char*)&stan_paletkaPos, sizeof(stan_paletkaPos));
    ofs.write((char*)&stan_pilkaPos, sizeof(stan_pilkaPos));
    ofs.write((char*)&stan_pilkaVel, sizeof(stan_pilkaVel));

    size_t count = stan_bloki.size();
    ofs.write((char*)&count, sizeof(count));

    if (count > 0) {
        ofs.write((char*)stan_bloki.data(), count * sizeof(BlockData));
    }
    ofs.close();
    return true;
}

bool GameState::stan_wczytajZPliku(const std::string& nazwa_pliku) {
    std::ifstream ifs(nazwa_pliku, std::ios::binary);
    if (!ifs.is_open()) {
        return false; 
    }

    ifs.read((char*)&stan_paletkaPos, sizeof(stan_paletkaPos));
    ifs.read((char*)&stan_pilkaPos, sizeof(stan_pilkaPos));
    ifs.read((char*)&stan_pilkaVel, sizeof(stan_pilkaVel));

    size_t count = 0;
    ifs.read((char*)&count, sizeof(count));

    stan_bloki.resize(count); 

    if (count > 0) {
        ifs.read((char*)stan_bloki.data(), count * sizeof(BlockData));
    }

    ifs.close();
    return true;
}