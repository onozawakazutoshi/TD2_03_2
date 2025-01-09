#pragma once
#include <vector>
#include <Novice.h>

struct Rect {
    int x, y, width, height;
    unsigned int color;
};

class Player {
private:
    std::vector<Rect> rectangles; // 矩形列表
    const int maxRectangles = 4;  // 最大矩形数量

public:
    Player() = default; // 默认构造函数
    Player(const Player& other) {
        rectangles = other.rectangles;
    }
    ~Player() = default; // 默认析构函数

    Player& operator=(const Player& other) {
        if (this != &other) {
            rectangles = other.rectangles;
        }
        return *this;
    }

    void AddRectangle(int x, int y, int width, int height, unsigned int color) {
        if (rectangles.size() < maxRectangles) {
            rectangles.push_back({x, y, width, height, color});
        }
    }

    void RemoveLastRectangle() {
        if (!rectangles.empty()) {
            rectangles.pop_back();
        }
    }

    void DrawRectangles() const {
        for (const auto& rect : rectangles) {
            Novice::DrawBox(
                rect.x,
                rect.y,
                rect.width,
                rect.height,
                0.0f,
                rect.color,
                kFillModeSolid
            );
        }
    }

    int GetRectangleCount() const {
        return static_cast<int>(rectangles.size());
    }
};
