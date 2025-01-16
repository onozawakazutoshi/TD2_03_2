#pragma once
#include <vector>
#include <Novice.h>

class Enemy {
public:
    float x;  // X座標
    float y;  // Y座標
    float width;  // 幅
    float height; // 高さ
    unsigned int color; // 色 (RGBA)

    Enemy(float startX, float startY, float startWidth, float startHeight, unsigned int startColor);
    void Draw() const;
};
