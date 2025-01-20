#pragma once
#include <vector>
#include "Player.h"
#include "Enemy.h"
#include "Map.h"

struct GameState {
    std::vector<Player> players;
    std::vector<Enemy> enemies;
    Map::MapData currentMap;
};
