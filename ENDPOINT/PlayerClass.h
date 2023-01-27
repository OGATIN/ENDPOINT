#include"GameObject.h"
#pragma once

class PlayerClass
{
public:
	GameObject gameobject;

	PlayerClass() {};
	PlayerClass(Texture _animation[4][20], Audio _audio[19], CSV AnimationData, CSV statusData)
	{
		for (int j = 0; j < 4; j++)
		{
			for (int i = 0; i < 7; i++)
			{
				//とりあえず共通のデータはここでロード
				gameobject.animation[j][i].Reload(_animation[j][i], AnimationData, i + 1);
			}
		}

		for (int i = 0; i < 19; i++)
		{
			gameobject.audio[i] = _audio[i];
		}

		gameobject.status.Reload(statusData);
	};


};

