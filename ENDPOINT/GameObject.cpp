#include "stdafx.h"
#include "GameObject.h"

void GameObject::Update()
{
	//当たり判定更新
	hitBox = GetHitRect();

	//座標更新
	position += velocity;

	//重力加算
	velocity.y += gravity;

}

void GameObject::MotionStart()
{
	switch (state)
	{
	case StateType::WAIT:
		waitMotion.currentTime.start();
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


void GameObject::MotionStop()
{
	//ストップウォッチが停止しているか
	if (waitMotion.currentTime.isRunning())
	{
		//計測中なら停止(経過時間はそのまま)
		switch (state)
		{
		case StateType::WAIT:
			waitMotion.currentTime.pause();
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
	else
	{
		//停止中なら計測
		switch (state)
		{
		case StateType::WAIT:
			waitMotion.currentTime.resume();
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
}

void GameObject::Jump()
{
	velocity.y = -jumpPower;
}

void GameObject::Walk()
{
	if (isMirror)
	{
		position.x += charaSpeed;
	}
	else
	{
		position.x -= charaSpeed;
	}	
}

void GameObject::Move()
{
	//左右移動(仮)
	if (KeyRight.pressed() || KeyD.down())
	{
		position.x += charaSpeed;
	}
	if (KeyLeft.pressed() || KeyA.down())
	{
		position.x -= charaSpeed;
	}
}


void GameObject::StateManagement()
{
	/*Update();*/

	ChangeState();


	switch (state)
	{
	case StateType::WAIT:
		waitMotion.PatternLoop();
		break;
	case StateType::WAIK:
		walkMotion.PatternLoop();
		Walk();
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

void GameObject::StateManagementDraw() const
{
	switch (state)
	{
	case StateType::WAIT:
		waitMotion.Draw(position);
		break;
	case StateType::WAIK:
		walkMotion.Draw(position);
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

void GameObject::ChangeState()
{
	bool defaultState = (state == StateType::WAIT || state == StateType::WAIK || state == StateType::RUN);

	if (isHit)
	{
		state == StateType::RECEIVE;
	}

	if (state != StateType::RECEIVE)
	{
		if (not isMotionLock)
		{
			state = StateType::WAIT;
		}

		if (not isMotionLock && KeyD.pressed() || KeyRight.pressed())
		{
			state = StateType::WAIK;
			isMirror = false;
		}

		if (not isMotionLock && KeyA.pressed() || KeyLeft.pressed())
		{
			state = StateType::WAIK;
			isMirror = true;
		}

		if (not isMotionLock && KeyControl.pressed() && KeyD.pressed() || KeyRight.pressed())
		{
			state = StateType::RUN;
			isMirror = false;
		}

		if (not isMotionLock && KeyControl.pressed() && KeyA.pressed() || KeyLeft.pressed())
		{
			state = StateType::RUN;
			isMirror = true;
		}

		if (KeySpace.down() && defaultState)
		{
			state = StateType::JUMP;
		}

		if (KeyZ.down() && defaultState)
		{
			state = StateType::ATTACK;
		}

		if (KeyX.down() && defaultState)
		{
			state = StateType::MAGIC;
		}

		if (KeyShift.pressed() && defaultState)
		{
			state = StateType::GUARD;
		}
	}
}

/////////////////////////////////////////////////////////////
//														   //
//														   //
//				　　　　デバック用						   //
//														   //
//														   //
/////////////////////////////////////////////////////////////


void GameObject::Initialize()
{
	//初期座標
	position = { 400,425 };

	//初期移動量
	velocity = { 0,0 };

	//時間管理用
	animationTime.start();
}

