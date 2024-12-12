//#include "Player.h"
//
//using namespace KamataEngine;
//
//void Player::Initialize() {
//	gameMap->Initialize();
//	player_ = { 0.0f,0.0f };
//	Radius_ = 32;
//	move_ = { 0.0f,0.0f };
//	newmove_ = 2.0f;
//
//	SetInitialPosition(player_,6,12,0);
//}
//
//
//
//
//
//void Player::Update(char* keys, char* preKeys) {
//
//	move_.x = 0.0f;
//	move_.y = 0.0f;
//
//	if (keys[DIK_D]) {
//	
//	}
//	if (preKeys[DIK_D]) {
//
//	}
//
	/*	Vector2 LeftTop = { (player_.x) / blocksizu,(player_.y) / blocksizu };
		Vector2 RightTop = { (player_.x + Radius - 1) / blocksizu,(player_.y) / blocksizu };
		Vector2 LeftBottom = { (player_.x) / blocksizu,(player_.y + Radius - 1) / blocksizu };
		Vector2 RightBottom = { (player_.x + Radius - 1) / blocksizu,(player_.y + Radius - 1) / blocksizu };*/

//	// }
//	//// 右方向（Dキー）
//	//if (keys[DIK_D]) {
//	//	RightTop.x = ((player_.x + Radius) - 1 + move2) / blocksizu;
//	//	RightBottom.x = ((player_.x + Radius) - 1 + move2) / blocksizu;
//	//	if (RightTop.x >= 0 && RightTop.x < MapWidth && RightBottom.x >= 0 && RightBottom.x < MapWidth) {
//	//		if (MAPdeta[(int)RightTop.y][(int)RightTop.x] == targetchip && MAPdeta[(int)RightBottom.y][(int)RightBottom.x] == targetchip) {
//	//			move.x = move2;
//	//		}
//	//	}
//	//}
//
//	//// 左方向（Aキー）
//	//if (keys[DIK_A]) {
//	//	LeftTop.x = (player.x - move2) / blocksizu;
//	//	LeftBottom.x = (player.x - move2) / blocksizu;
//	//	if (LeftTop.x >= 0 && LeftTop.x < MapWidth && LeftBottom.x >= 0 && LeftBottom.x < MapWidth) {
//	//		if (MAPdeta[(int)LeftTop.y][(int)LeftTop.x] == targetchip && MAPdeta[(int)LeftBottom.y][(int)LeftBottom.x] == targetchip) {
//	//			move.x = -move2;
//	//		}
//	//	}
//	//}
//
//	//// 上方向（Wキー）
//	//if (keys[DIK_W]) {
//	//	LeftTop.y = (player.y - move2) / blocksizu;
//	//	RightTop.y = (player.y - move2) / blocksizu;
//	//	if (LeftTop.y >= 0 && LeftTop.y < MapHeight && RightTop.y >= 0 && RightTop.y < MapHeight) {
//	//		if (MAPdeta[(int)LeftTop.y][(int)LeftTop.x] == targetchip && MAPdeta[(int)RightTop.y][(int)RightTop.x] == targetchip) {
//	//			move.y = -move2;
//	//		}
//	//	}
//	//}
//
//	//// 下方向（Sキー）
//	//if (keys[DIK_S]) {
//	//	LeftBottom.y = ((player.y + Radius) - 1 + move2) / blocksizu;
//	//	RightBottom.y = ((player.y + Radius) - 1 + move2) / blocksizu;
//	//	if (LeftBottom.y >= 0 && LeftBottom.y < MapHeight && RightBottom.y >= 0 && RightBottom.y < MapHeight) {
//	//		if (MAPdeta[(int)LeftBottom.y][(int)LeftBottom.x] == targetchip && MAPdeta[(int)RightBottom.y][(int)RightBottom.x] == targetchip) {
//	//			move.y = move2;
//	//		}
//	//	}
//	//}
//
//	player_.x += move_.x;
//	player_.y += move_.y;
//}
//
//void Player::Draw() {
//	Novice::ScreenPrintf(400, 0, " player X :%f", player_.x);
//	Novice::ScreenPrintf(400, 15, " player Y :%f", player_.y);
//
//
//
//
//	Novice::DrawBox(int(player_.x), int(player_.y), Radius_, Radius_, 0.0f, RED, kFillModeSolid);
//}
//
//
//
//void Player::SetInitialPosition(Vector2& player, int startX, int startY, int targetchip) {
//	// 指定された座標がマップの範囲内か確認
//	if (startX >= 0 && startX < gameMap->GetHeight() && startY >= 0 && startY < gameMap->GetWidth()) {
//		// 指定されたマスが移動可能か確認
//		if (gameMap->GetMapValue(startY,startX) == targetchip) {
//			player.x = float(startX) * 32; 
//			player.y = float(startY) * 32; 
//		}
//	}
//}