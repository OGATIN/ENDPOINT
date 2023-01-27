#include"GameObject.h"
#pragma once

class PlayerClass
{
public:
	GameObject gameobject;
	int MaxHitPoint;
	int MaxMagicPoint;
	int MaxMentalPoint;
	int MaxStaminaPoint;
	Bar hitpointBar{ MaxHitPoint };
	Bar magicpointBar{ MaxMagicPoint ,Palette::Blue};
	Bar mentalpointBar{ MaxMentalPoint ,Palette::Purple};
	Bar staminapointBar{ MaxMentalPoint ,Palette::Yellow};

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
		MaxHitPoint = gameobject.status.hitPoints;
		MaxMagicPoint = gameobject.status.magicPoint;
		MaxMentalPoint = gameobject.status.mental;
		MaxStaminaPoint = gameobject.status.stamina;
	};



	void Update();

	void StatusDraw()const;

	void Draw()const;

	void DebugDraw()const;
};

