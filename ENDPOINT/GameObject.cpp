#include "stdafx.h"
#include "GameObject.h"

void GameObject::Update()
{
	//当たり判定更新
	//hitBox = GetHitRect();

	//座標更新
	position += velocity;

	//重力加算
	velocity.y += gravity;

	//重量定義
	if (status.weight < charaSpeedMax)
	{
		charaSpeed = status.weight;
	}
	else
	{
		charaSpeed = charaSpeedMax;
	}

	//重量定義
	if (status.weight < jumpPowerMax)
	{
		jumpPower = status.weight;
	}
	else
	{
		jumpPower = charaSpeedMax;
	}
	
	//Xベクトル減少
	if (state != StateType::JUMP)
	{
		if (velocity.x > 0)
		{
			velocity.x -= 1;
		}

		if (velocity.x < 0)
		{
			velocity.x += 1;
		}
	}
	
}

void GameObject::MotionStart()
{
	currentTime.start();
}


void GameObject::MotionStop()
{
	//ストップウォッチが停止しているか
	if (currentTime.isRunning())
	{
		//計測中なら停止(経過時間はそのまま)
		currentTime.pause();
	}
	else
	{
		//停止中なら計測
		currentTime.resume();
	}

}

void GameObject::PatternLoop()
{ 
	//タイル遷移
	if (currentTime.ms() > animation[weaponTypeNumber][stateTypeNumber].OnePatternMotionTime())
	{
		animation[weaponTypeNumber][stateTypeNumber].cutPos.x++;
		currentTime.restart();
	}

	//ループ
	if (animation[weaponTypeNumber][stateTypeNumber].cutPos.x >= animation[weaponTypeNumber][stateTypeNumber].endPattern)
	{
		animation[weaponTypeNumber][stateTypeNumber].cutPos.x = animation[weaponTypeNumber][stateTypeNumber].startPattern;

		animation[weaponTypeNumber][stateTypeNumber].elapsedTime = 0;
	}

	//デバック用
	animation[weaponTypeNumber][stateTypeNumber].elapsedTime = (animation[weaponTypeNumber][stateTypeNumber].OnePatternMotionTime() * animation[weaponTypeNumber][stateTypeNumber].cutPos.x) + currentTime.ms();

}


void GameObject::WalkProcess()
{
	//反転してる向きに応じて処理
	if (isMirror)
	{
		velocity.x = - charaSpeed;
	}
	else
	{
		velocity.x =  charaSpeed;
	}

	if (state == StateType::WALK && velocity.x == 0)
	{
		state = StateType::WAIT;
	}
}

void GameObject::RunProcess()
{
	//反転してる向きに応じて処理
	if (isMirror)
	{
		velocity.x = - charaSpeed * 1.5;
	}
	else
	{
		velocity.x = charaSpeed * 1.5;
	}

	if (state == StateType::RUN && velocity.x == 0)
	{
		state = StateType::WAIT;
	}
}

//要検討
void GameObject::JumpProcess()
{
	velocity.y = -jumpPower;
}

void GameObject::ChangeWait()
{
	if (state == StateType::WALK || state == StateType::RUN || state == StateType::JUMP || state == StateType::MAGIC || state == StateType::GUARD || state == StateType::RECEIVE)
	{
		state = StateType::WAIT;
	}
}

void GameObject::ChangeWalkR()
{
	if (state == StateType::WAIT || state == StateType::RUN)
	{
		state = StateType::WALK;
		isMirror = false;
	}
}

void GameObject::ChangeWalkL()
{
	if (state == StateType::WAIT || state == StateType::RUN)
	{
		state = StateType::WALK;
		isMirror = true;
	}
}

void GameObject::ChangeRunR()
{
	if (state == StateType::WAIT || state == StateType::WALK)
	{
		state = StateType::RUN;
		isMirror = false;
	}	
}

void GameObject::ChangeRunL()
{
	if (state == StateType::WAIT || state == StateType::WALK)
	{
		state = StateType::RUN;
		isMirror = true;
	}
}

void GameObject::ChangeJump()
{
	if (state == StateType::WAIT || state == StateType::WALK || state == StateType::RUN || state == StateType::RECEIVE)
	{
		state = StateType::JUMP;
	}
}



void GameObject::StateManagement()
{
	switch (state)
	{
	case StateType::WAIT:
		stateTypeNumber = 0;
		statename = {U"待機"};
		break;
	case StateType::WALK:
		WalkProcess();
		stateTypeNumber = 1;
		statename = { U"歩き" };
		break;
	case StateType::RUN:
		RunProcess();
		stateTypeNumber = 2;
		statename = { U"走り" };
		break;
	case StateType::JUMP:
		JumpProcess();
		stateTypeNumber = 3;
		statename = { U"ジャンプ" };
		break;
	case StateType::RECEIVE:
		stateTypeNumber = 4;
		statename = { U"受け" };
		break;
	case StateType::ATTACK:
		stateTypeNumber = 5;
		statename = { U"攻撃" };
		break;
	case StateType::MAGIC:
		stateTypeNumber = 6;
		statename = { U"魔法" };
		break;
	case StateType::GUARD:
		stateTypeNumber = 7;
		statename = { U"ガード" };
		break;
	case StateType::NOTSTAMINA:
		stateTypeNumber = 8;
		statename = { U"スタミナ切れ" };
		break;
	default:
		break;
	}

	switch (weapon)
	{
	case WeaponType::FIST:
		weaponname = { U"拳" };
		break;
	case WeaponType::SWORD:
		weaponname = { U"剣" };
		break;
	case WeaponType::HAMMER:
		weaponname = { U"鈍器" };
		break;
	case WeaponType::CANE:
		weaponname = { U"杖" };
		break;
	default:
		break;
	}
}

void GameObject::Draw() const
{
	animation[weaponTypeNumber][stateTypeNumber].Draw(position,isMirror);
}

void GameObject::ChangeState()
{
	bool defaultState = (state == StateType::WAIT || state == StateType::WALK || state == StateType::RUN);

	if (isHit)
	{
		state = StateType::RECEIVE;
	}

	if (state != StateType::RECEIVE)
	{
		if (not isMotionLock)
		{
			state = StateType::WAIT;
		}

		if (not isMotionLock && (KeyD.pressed() || KeyRight.pressed()))
		{
			state = StateType::WALK;
			isMirror = false;
		}

		if (not isMotionLock && (KeyA.pressed() || KeyLeft.pressed()))
		{
			state = StateType::WALK;
			isMirror = true;
		}

		if (not isMotionLock && KeyControl.pressed() && (KeyD.pressed() || KeyRight.pressed()))
		{
			state = StateType::RUN;
			isMirror = false;
		}

		if (not isMotionLock && KeyControl.pressed() && (KeyA.pressed() || KeyLeft.pressed()))
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
	position = { 250,125 };

	//初期移動量
	velocity = { 0,0 };

	//時間管理用
	/*animationTime.start();ここなのかな？*/
}

void GameObject::StatusDraw() const
{
	font30(U"状態 ", statename).draw(Scene::Width() - font30(U"状態 ", statename).region().w, font30.height() * 0);
	font30(U"武器 ", weaponname).draw(Scene::Width() - font30(U"状態 ", weaponname).region().w, font30.height() * 1);
}

void GameObject::TimeDebuggDraw() const
{
	font30(U"全体時間 ", animation[weaponTypeNumber][stateTypeNumber].motionTime).draw(Scene::Width() - font30(U"全体時間 ", animation[weaponTypeNumber][stateTypeNumber].motionTime).region().w, font30.height() * 2);
	font30(U"経過時間 ", animation[weaponTypeNumber][stateTypeNumber].elapsedTime).draw(Scene::Width() - font30(U"経過時間 ", animation[weaponTypeNumber][stateTypeNumber].elapsedTime).region().w, font30.height() * 3);
	font30(U"1枚あたりの時間 ", currentTime.ms()).draw(Scene::Width() - font30(U"1枚あたりの時間 ", currentTime.ms()).region().w, font30.height() * 4);
	font30(U"切り取り位置 ", animation[weaponTypeNumber][stateTypeNumber].cutPos).draw(Scene::Width() - font30(U"切り取り位置 ", animation[weaponTypeNumber][stateTypeNumber].cutPos).region().w, font30.height() * 5);

}


