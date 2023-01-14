#include"StatusClass.h"
#include"AnimationClass.h"
#pragma once

class PlayerClass
{
public:
	StatusClass playerStatus;


	PlayerClass() {};
	PlayerClass(CSV statusData)
	{
		playerStatus.Reload(statusData);
	};

};

