#pragma once
#include <vector>
#include "Paddle.h"
#include "Ball.h"
#include "Brick.h"
#include "GameState.h"

enum class StanGry {
    MENU,
    GRA,
    PAUZA,
    WYGRANA,
    PRZEGRANA
};

class GameLogic {
public:
    static void resetujKlocki(std::vector<Brick>&);
    static void aktualizuj(Paddle&, Ball&, std::vector<Brick>&, StanGry&, int);
    static void przywroc(Paddle&, Ball&, std::vector<Brick>&, const GameState&);
};
