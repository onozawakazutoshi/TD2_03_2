#pragma once
#include <stdio.h>
#include<math/Vector2.h>

class MapData
{
	// �}�b�v�̐�
	static const int MaxMapCount = 3;
	// �}�b�v�̕��A����
	static const int MaxMapWidth = 50;
	static const int MaxMapHeight = 7;

	struct mapData {
		int MAP[MaxMapHeight][MaxMapWidth];		        	                // �}�b�v�̃T�C�Y
		KamataEngine::Vector2 mapSizes[MaxMapCount];	                	// �e�}�b�v���Ƃ�Width,Height���w��
		int Width = 0;                                 	                    // �}�b�v�̕�
		int Height = 0;                        	                            // �}�b�v�̍���
		int size; 		                        	                        // �}�b�v�`�b�v�̃T�C�Y
		unsigned int color[MaxMapHeight][MaxMapWidth]{};            		// �}�b�v�`�b�v�̃J���[
		KamataEngine::Vector2 Mapposition[MaxMapHeight][MaxMapWidth]{};		// �}�b�v�`�b�v�̍��W
		KamataEngine::Vector2 Mapstart;		                                // �}�b�v�`�b�v�̊J�n���W
	};
};

