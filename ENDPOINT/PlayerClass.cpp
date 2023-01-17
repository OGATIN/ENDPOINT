﻿#include"PlayerClass.h"
#pragma once

Rect PlayerClass::GetHitRect()
{
	return Rect{ (int)position.x + playerAnimation.waitPosDifference.x
				,(int)position.y + playerAnimation.waitPosDifference.y
				,playerAnimation.waitPosDifference.w,playerAnimation.waitPosDifference.h };
}

int PlayerClass::GetTop()
{
	return (int)position.y + playerAnimation.waitPosDifference.y;
}

int PlayerClass::GetBottom()
{
	return (int)position.y + playerAnimation.waitPosDifference.y + playerAnimation.waitPosDifference.h;
}

int PlayerClass::GetLeft()
{
	return (int)position.x + playerAnimation.waitPosDifference.x;
}

int PlayerClass::GetRight()
{
	return (int)position.x + playerAnimation.waitPosDifference.x + playerAnimation.waitPosDifference.w;
}




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

void PlayerClass::StateManagementDraw() const
{
	switch (state)
	{
	case StateType::WAIT:
		playerAnimation.WaitDraw(position);
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
