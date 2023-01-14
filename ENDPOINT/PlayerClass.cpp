#include"PlayerClass.h"
#pragma once

void PlayerClass::StateManagement()
{
	switch (state)
	{
	case StateType::WAIT:
		playerAnimation.Wait();
		break;
	case StateType::WAIK:
		break;
	case StateType::RUN:
		break;
	case StateType::JUMP:
		break;
	case StateType::RECEIVE:
		break;
	case StateType::ATTACK:
		break;
	case StateType::MAGIC:
		break;
	case StateType::GUARD:
		break;
	case StateType::NOTSTAMINA:
		break;
	default:
		break;
	}
}

void PlayerClass::MotionStart()
{
	playerAnimation.currentTime.start();//再開にも使えます。
}

void PlayerClass::MotionStop()
{
	//ストップウォッチが停止しているか
	if (playerAnimation.currentTime.isRunning())
	{
		//計測中なら停止(経過時間はそのまま)
		playerAnimation.currentTime.pause();
	}
	else
	{
		//停止中なら計測
		playerAnimation.currentTime.resume();
	}
}
