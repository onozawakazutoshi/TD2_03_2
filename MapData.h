#pragma once
#include <stdio.h>
#include<math/Vector2.h>

class MapData
{
	// マップの数
	static const int MaxMapCount = 3;
	// マップの幅、高さ
	static const int MaxMapWidth = 50;
	static const int MaxMapHeight = 7;

	struct mapData {
		int MAP[MaxMapHeight][MaxMapWidth];		        	                // マップのサイズ
		KamataEngine::Vector2 mapSizes[MaxMapCount];	                	// 各マップごとにWidth,Heightを指定
		int Width = 0;                                 	                    // マップの幅
		int Height = 0;                        	                            // マップの高さ
		int size; 		                        	                        // マップチップのサイズ
		unsigned int color[MaxMapHeight][MaxMapWidth]{};            		// マップチップのカラー
		KamataEngine::Vector2 Mapposition[MaxMapHeight][MaxMapWidth]{};		// マップチップの座標
		KamataEngine::Vector2 Mapstart;		                                // マップチップの開始座標
	};
};

