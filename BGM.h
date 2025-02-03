#pragma once
#include "Novice.h"

class BGMManager {
public:

    ~BGMManager();

    void Initialize();

    void Update(int sceneState);

private:
    int selectHandle_;
    int coinHandle_;
    int gameBgmHandle_;
    int playHandle_; // 播放中的音频句柄
    bool isPlaying_; // 是否正在播放
};
