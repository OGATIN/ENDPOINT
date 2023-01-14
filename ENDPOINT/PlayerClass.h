#include"StatusClass.h"
#include"AnimationClass.h"
#pragma once

class PlayerClass
{
public:
	StatusClass playerStatus;//ステータス

	AnimationClass playerAnimation;//アニメーション

	StateType state = StateType::WAIT;

	PlayerClass() {};
	PlayerClass(Texture _wait,CSV statusData)
	{
		playerStatus.Reload(statusData);
		playerAnimation.Reload(_wait);
	};

	void StateManagement();
	void MotionStart();
	void MotionStop();

};

