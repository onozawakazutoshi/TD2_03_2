#pragma once
#include <Novice.h>

// ���`�󥯥饹
class GameScene
{
public: // �����v��
	// ���`���״�B��������В���
	enum class SceneState
	{
		Title,
		Game,
		Clear
	};

	// ���ڻ�
	void Initialize();
	// �����軭�I��
	int UpdateDraw();

private: // ���Љ���
	// ���`�����Y�����ܤ�ȡ����
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };
	// ���`��άF�ڤ�״�B
	SceneState currentState = SceneState::Game;// ���ڤΥ��`��
};