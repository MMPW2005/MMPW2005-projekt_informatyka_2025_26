#include "GameState.h"
#include <fstream>

void GameState::zapisz(const Paddle& p, const Ball& b, const std::vector<Brick>& k) {
    paletkaPos = p.paletka_ksztalt.getPosition();
    pilkaPos = b.pilka_ksztalt.getPosition();
    pilkaVel = b.pilka_pobierzVel();
    bloki.clear();
    for (auto& klocek : k) {
        bloki.push_back({ klocek.klocek_ksztalt.getPosition().x, klocek.klocek_ksztalt.getPosition().y, klocek.klocek_hp });
    }
}

bool GameState::zapiszDoPliku(const std::string& n) const {
    std::ofstream f(n, std::ios::binary);
    if (!f) {
        return false;
    }
    size_t count = bloki.size();
    f.write((char*)&paletkaPos, sizeof(paletkaPos));
    f.write((char*)&pilkaPos, sizeof(pilkaPos));
    f.write((char*)&pilkaVel, sizeof(pilkaVel));
    f.write((char*)&count, sizeof(count));
    if (count > 0) {
        f.write((char*)bloki.data(), count * sizeof(BlockData));
        return true;
    }
}

bool GameState::wczytajZPliku(const std::string& n) {
    std::ifstream f(n, std::ios::binary);
    if (!f) {
        return false;
    }
    size_t count;
    f.read((char*)&paletkaPos, sizeof(paletkaPos));
    f.read((char*)&pilkaPos, sizeof(pilkaPos));
    f.read((char*)&pilkaVel, sizeof(pilkaVel));
    f.read((char*)&count, sizeof(count));
    bloki.resize(count);
    if (count > 0) {
        f.read((char*)bloki.data(), count * sizeof(BlockData));
        return true;
    }
}
