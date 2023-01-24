#pragma once
#include"GameObject.h"

class EnemyClass
{
public:
	GameObject shaft;



	EnemyClass(Texture _animation[4][20], CSV AnimationData, CSV statusData)
	{
		shaft.Reload(_animation, AnimationData, statusData);

	};

};

