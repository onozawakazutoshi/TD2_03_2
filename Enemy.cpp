#include "Enemy.h"

Enemy::Enemy(float startX, float startY, float startWidth, float startHeight, unsigned int startColor)
    : x(startX), y(startY), width(startWidth), height(startHeight), color(startColor) {}

void Enemy::Draw() const {
    Novice::DrawBox(
        static_cast<int>(x - width / 2),
        static_cast<int>(y - height / 2),
        static_cast<int>(width),
        static_cast<int>(height),
        0.0f,
        color,
        kFillModeSolid
    );
}

