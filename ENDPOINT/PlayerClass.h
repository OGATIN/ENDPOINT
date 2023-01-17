#include"StatusClass.h"
#include"AnimationClass.h"
#pragma once

class PlayerClass
{
public:
	StatusClass playerStatus;//ステータス

	AnimationClass playerAnimation;//アニメーション

	StateType state = StateType::WAIT;

	Vec2 position = {0,0};
	Vec2 velocity = {0,0};
	Rect hitBox = {0,0,0,0};

	double gravity = 0.2;
	bool isJump = false;

	int jumpPower = 8;
	int playerSpeed = 3;

	PlayerClass() {};
	PlayerClass(Texture _wait,CSV statusData)
	{
		playerStatus.Reload(statusData);
		playerAnimation.Reload(_wait);
	};

	Rect GetHitRect();
	int GetTop();
	int GetBottom();
	int GetLeft();
	int GetRight();
	void StateManagement();
	void StateManagementDraw()const;
	void MotionStart();
	void MotionStop();

};

