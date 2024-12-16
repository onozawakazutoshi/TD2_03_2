#include "Player.h"
#include <Novice.h>

using namespace KamataEngine;

void Player::Initialize() {


	position = { 640.0f, 360.0f };
	radius = 14;


}

void Player::Update() {





}

void Player::Draw() {
	Novice::DrawEllipse(int(position.x),int(position.y), radius, radius,0.0f,RED,kFillModeSolid);
}