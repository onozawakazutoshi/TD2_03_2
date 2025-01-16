#pragma once
#include <deque>
#include <vector>
#include <memory>
#include "GameState.h"

// テンプレートクラス: 任意のエンティティの状態管理を行う
template <typename T>
class GameStateManager {
private:
    std::deque<T> history;          // 過去の状態を保存するデータ構造
    std::deque<T> fastForwardHistory; // 未来の状態を保存するデータ構造
    int maxHistory;                        // 最大履歴数
    bool isRestoringState = false;

public:
    // コンストラクタ: 最大履歴数を設定
    GameStateManager(int maxFrames);

    // 現在の状態を保存する関数
    void SaveState(const T& entities);

    // 状態を巻き戻す関数
    void UndoState(T& entities, int frames);

    // 状態を早送りする関数
    void RedoState(T& entities, int frames);

    int GetCurrentFrame() const {
    return static_cast<int>(history.size());
}
};
