#include"PlayerClass.h"
#pragma once

//Rect PlayerClass::GetHitRect()
//{
//	return Rect{ (int)position.x + playerAnimation.waitPosDifference.x
//				,(int)position.y + playerAnimation.waitPosDifference.y
//				,playerAnimation.waitPosDifference.w,playerAnimation.waitPosDifference.h };
//}
//
//int PlayerClass::GetTop()
//{
//	return (int)position.y + playerAnimation.waitPosDifference.y;
//}
//
//int PlayerClass::GetBottom()
//{
//	return (int)position.y + playerAnimation.waitPosDifference.y + playerAnimation.waitPosDifference.h;
//}
//
//int PlayerClass::GetLeft()
//{
//	return (int)position.x + playerAnimation.waitPosDifference.x;
//}
//
//int PlayerClass::GetRight()
//{
//	return (int)position.x + playerAnimation.waitPosDifference.x + playerAnimation.waitPosDifference.w;
//}
//
//
//
//
//void PlayerClass::StateManagement()
//{
//	switch (state)
//	{
//	case StateType::WAIT:
//		playerAnimation.Wait();
//		break;
//	case StateType::WAIK:
//		break;
//	case StateType::RUN:
//		break;
//	case StateType::JUMP:
//		break;
//	case StateType::RECEIVE:
//		break;
//	case StateType::ATTACK:
//		break;
//	case StateType::MAGIC:
//		break;
//	case StateType::GUARD:
//		break;
//	case StateType::NOTSTAMINA:
//		break;
//	default:
//		break;
//	}
//}
//
//void PlayerClass::StateManagementDraw() const
//{
//	switch (state)
//	{
//	case StateType::WAIT:
//		playerAnimation.WaitDraw(position);
//		break;
//	case StateType::WAIK:
//		break;
//	case StateType::RUN:
//		break;
//	case StateType::JUMP:
//		break;
//	case StateType::RECEIVE:
//		break;
//	case StateType::ATTACK:
//		break;
//	case StateType::MAGIC:
//		break;
//	case StateType::GUARD:
//		break;
//	case StateType::NOTSTAMINA:
//		break;
//	default:
//		break;
//	}
//}

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

void PlayerClass::Jump()
{
	//↑が押されたらジャンプ
	if (KeyUp.down())
	{
		velocity.y = - jumpPower;
	}
}

void PlayerClass::Move()
{
	//左右移動(仮)
	if (KeyRight.pressed() || KeyD.down())
	{
		position.x += playerSpeed;
	}
	if (KeyLeft.pressed() || KeyA.down())
	{
		position.x -= playerSpeed;
	}
}

void PlayerClass::Initialize()
{
	//初期座標
	position = { 400,425 };

	//初期移動量
	velocity = { 0,0 };

	//ストップウォッチスタート
	MotionStart();
}

//void PlayerClass::PlayerUpdate()
//{
//	//当たり判定更新
//	hitBox = GetHitRect();
//
//	//座標更新
//	position += velocity;
//
//	//重力加算
//	velocity.y += gravity;
//
//	//状態管理
//	StateManagement();
//
//	Jump();
//
//	Move();
//
//	//デバック用
//	playerStatus.DaseStatusUpdate();//ステータスの表示
//
//	if (KeySpace.down())
//	{
//		//一時停止
//		MotionStop();
//	}
//}
//
//void PlayerClass::PlayerDraw() const
//{
//	//画像描画
//	StateManagementDraw();
//
//	//デバック用
//	playerStatus.DaseStatusDrow();//ステータスの表示
//	//playerAnimation.TimeDrow();//時間の表示
//}
