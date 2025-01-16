#pragma once
#include <vector>
#include "Player.h"
#include "Enemy.h"

struct GameState {
    std::vector<Player> players;
    std::vector<Enemy> enemies;
};
