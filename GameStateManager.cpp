#include "GameStateManager.h"

// コンストラクタ: 最大履歴数を初期化
template <typename T>
GameStateManager<T>::GameStateManager(int maxFrames) : maxHistory(maxFrames) {}

// 現在の状態を履歴に保存する
template <typename T>
void GameStateManager<T>::SaveState(const std::vector<T>& entities) {
    // 最大履歴数を超えた場合は最古の状態を削除する
  /*  if (history.size() >= maxHistory) {
        history.pop_front();
    }*/
    history.push_back(entities);
}

// 指定したフレーム分だけ状態を巻き戻す
template <typename T>
void GameStateManager<T>::UndoState(std::vector<T>& entities, int frames) {
    if (!history.empty()) {
        if (history.size() <= frames) {
            // 全て巻き戻す場合
            fastForwardHistory.insert(fastForwardHistory.begin(), history.begin(), history.end());
            entities = history.front();
            history.clear();
        } else {
            // 一部だけ巻き戻す場合
            auto startIt = history.end() - frames;
            fastForwardHistory.insert(fastForwardHistory.begin(), startIt, history.end());
            entities = *(startIt - 1);
            history.erase(startIt, history.end());
        }
    }
}

// 指定したフレーム分だけ状態を早送りする
// 巻き戻すしたら
template <typename T>
void GameStateManager<T>::RedoState(std::vector<T>& entities, int frames) {
    if (!fastForwardHistory.empty()) {
        if (fastForwardHistory.size() <= frames) {
            // 全て早送りする場合
            history.insert(history.end(), fastForwardHistory.begin(), fastForwardHistory.end());
            entities = fastForwardHistory.back();
            fastForwardHistory.clear();
        } else {
            // 一部だけ早送りする場合
            auto endIt = fastForwardHistory.begin() + frames;
            history.insert(history.end(), fastForwardHistory.begin(), endIt);
            entities = *(endIt - 1);
            fastForwardHistory.erase(fastForwardHistory.begin(), endIt);
        }
    }
}

// 明示的インスタンス化: Player型のテンプレートクラスを生成
template class GameStateManager<Player>;
