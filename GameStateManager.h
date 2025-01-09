#pragma once
#include <deque>
#include <vector>
#include <memory>
#include "Player.h"

// テンプレートクラス: 任意のエンティティの状態管理を行う
template <typename T>
class GameStateManager {
private:
    std::deque<std::vector<T>> history;          // 過去の状態を保存するデータ構造
    std::deque<std::vector<T>> fastForwardHistory; // 未来の状態を保存するデータ構造
    const int maxHistory;                        // 最大履歴数

public:
    // コンストラクタ: 最大履歴数を設定
    GameStateManager(int maxFrames);

    // 現在の状態を保存する関数
    void SaveState(const std::vector<T>& entities);

    // 状態を巻き戻す関数
    void UndoState(std::vector<T>& entities, int frames);

    // 状態を早送りする関数
    void RedoState(std::vector<T>& entities, int frames);
};
