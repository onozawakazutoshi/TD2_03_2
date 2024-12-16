#include "Player.h"
#include <Novice.h>
#include <cmath> // sqrt, pow を使用するためにインクルード

using namespace KamataEngine;

void Player::Initialize() {


	position = { 640.0f, 360.0f };
	radius = 14;


}

void Player::Update(const char* keys) {


    if (keys[DIK_D]) {
      //  position.x += 2;
    }
    if (keys[DIK_A]) {
       // position.x -= 2;
    }
    if (keys[DIK_W]) {
       // position.y -= 2;
    }
    if (keys[DIK_S]) {
        //position.y += 2;
    }

}

void Player::Draw() {
	//Novice::DrawEllipse(int(position.x),int(position.y), radius, radius,0.0f,RED,kFillModeSolid);
}

