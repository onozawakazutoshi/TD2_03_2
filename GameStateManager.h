#pragma once
#include "Player.h"
#include <deque>

class GameStateManager {
private:
    std::deque<Player*> history; 
    std::deque<Player*> fastForwardHistory;
    const int maxHistoryFrames = 200;
    int frameCounter = 0;

public:
    Player* player;
     GameStateManager();
    ~GameStateManager();
    // 构造函数
    void Initialize();

    // 保存当前状态
    void SaveState();

    // 回退状态
    void UndoState(int frames);

    // 快进状态
    void RedoState(int frames);
};