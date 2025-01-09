#include "GameStateManager.h"

GameStateManager::GameStateManager() {
    player = new Player();
}

GameStateManager::~GameStateManager() {
    delete player;

    for (auto p : history) {
        delete p;
    }
    for (auto p : fastForwardHistory) {
        delete p;
    }
}
void GameStateManager::Initialize()
{
    history.clear();
    fastForwardHistory.clear();
}
// 保存当前状态
void GameStateManager::SaveState() {
    
    Player* savedPlayer = new Player(*player);
    history.push_back(savedPlayer);
     
}

// 回退状态
void GameStateManager::UndoState(int frames) {
    if (!history.empty()) {
        if (history.size() <= frames) {
            fastForwardHistory.insert(fastForwardHistory.begin(), history.begin(), history.end());
            player = history.front(); // 回退到最早状态
            history.clear();
        } else {
            auto startIt = history.end() - frames;
            fastForwardHistory.insert(fastForwardHistory.begin(), startIt, history.end());
            player = *(startIt - 1);
            history.erase(startIt, history.end());
        }
    }
}

// 快进状态
void GameStateManager::RedoState(int frames) {
    if (!fastForwardHistory.empty()) {
        if (fastForwardHistory.size() <= frames) {
            history.insert(history.end(), fastForwardHistory.begin(), fastForwardHistory.end());
            player = fastForwardHistory.back(); // 快进到最后状态
            fastForwardHistory.clear();
        } else {
            auto endIt = fastForwardHistory.begin() + frames;
            history.insert(history.end(), fastForwardHistory.begin(), endIt);
            player = *(endIt - 1);
            fastForwardHistory.erase(fastForwardHistory.begin(), endIt);
        }
    }
}