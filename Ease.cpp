#include "Ease.h"
#include <cmath>

namespace Ease
{
	float easeOutQuart(float t) {
		float oneMinusT = 1.0f - t;
		return 1.0f - (oneMinusT * oneMinusT * oneMinusT * oneMinusT);
	}

    // easeOutInSine イージング関数
    float easeOutInSine(float t) {
        if (t < 0.5f) {
            // 前半 (0.0 ～ 0.5) は EaseOut (減速)
            return 0.5f * (1.0f - cosf(t * 3.14159265359f / 1.0f));
        } else {
            // 後半 (0.5 ～ 1.0) は EaseIn (加速)
            return 0.5f * (1.0f - cosf((t - 0.5f) * 3.14159265359f / 1.0f));
        }
    }

    float easeOutInQuad(float t) {
        if (t < 0.5f) {
            // 前半 (0.0 ～ 0.5) は EaseOut (減速)
            return 2.0f * t * t;
        } else {
            // 後半 (0.5 ～ 1.0) は EaseIn (加速)
            t = 2.0f * t - 1.0f; // 0.5から1.0の範囲を0から1に変換
            return -0.5f * (t * (t - 2.0f) - 1.0f);
        }
    }



    float easeOutInCubic(float t) {
        if (t < 0.5f) {
            // 前半 (0.0 ～ 0.5) は急激に減速 (EaseOut)
            return 4.0f * t * t * t;  // 立方体のカーブで急激に減速
        } else {
            // 後半 (0.5 ～ 1.0) は急激に加速 (EaseIn)
            t = 2.0f * t - 1.0f;  // 0.5 から 1.0 の範囲を 0 から 1 に変換
            return 0.5f * (t * t * t + 1.0f);  // 立方体のカーブで急激に加速
        }
    }

    float easeOutQuint(float t) {
        return 1.0f - powf(1.0f - t, 5);
    }


}