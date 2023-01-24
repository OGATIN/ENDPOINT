#include "stdafx.h"
#include "GameObject.h"


void GameObject::Reload(Texture _animation[4][20], CSV AnimationData, CSV statusData)
{

	for (int j = 0; j < 4; j++)
	{
		for (int i = 0; i < 7; i++)
		{
			//とりあえず共通のデータはここでロード
			animation[j][i].Reload(_animation[j][i], AnimationData, i + 1);

		}
	}

	status.Reload(statusData);

}

void GameObject::Update()
{
	//当たり判定更新
	//hitBox = GetHitRect();

	//座標更新
	position += velocity;

	prePosition = position;

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
	if (state != StateType::FALLING && state != StateType::JUMP)
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

	if (state == StateType::JUMP)
	{
		if (velocity.x > 0)
		{
			velocity.x -= 0.1;
		}

		if (velocity.x < 0)
		{
			velocity.x += 0.1;
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
	OnePattern();

	//ループ
	if (animation[weaponTypeNumber][stateTypeNumber].cutPos.x >= animation[weaponTypeNumber][stateTypeNumber].endPattern)
	{
		animation[weaponTypeNumber][stateTypeNumber].cutPos.x = animation[weaponTypeNumber][stateTypeNumber].startPattern;

		animation[weaponTypeNumber][stateTypeNumber].elapsedTime = 0;
	}

	//デバック用
	animation[weaponTypeNumber][stateTypeNumber].elapsedTime = (animation[weaponTypeNumber][stateTypeNumber].OnePatternMotionTime() * motionEndMagnification * animation[weaponTypeNumber][stateTypeNumber].cutPos.x) + currentTime.ms();
}

void GameObject::OnePattern()
{
	//タイル遷移
	if (currentTime.ms() > (animation[weaponTypeNumber][stateTypeNumber].OnePatternMotionTime() * motionEndMagnification))
	{
		animation[weaponTypeNumber][stateTypeNumber].cutPos.x++;
		currentTime.restart();
	}
}

bool GameObject::isOneLoop()
{
	return animation[weaponTypeNumber][stateTypeNumber].cutPos.x >= animation[weaponTypeNumber][stateTypeNumber].endPattern;
}

void GameObject::WaitProcess()
{
	velocity.x = 0;
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
}

//要検討
void GameObject::JumpProcess()
{
	if (isOneLoop())
	{
		velocity.y = -jumpPower;
		state = StateType::FALLING;
	}
}

void GameObject::FallingProcess()
{
	if (isLanding)
	{
		state = StateType::WAIT;
	}
}

void GameObject::LandingProcess()
{

}

void GameObject::ReceiveProcess()
{
}

void GameObject::AttackProcess()
{
	if (isOneLoop())
	{
		state = StateType::WAIT;
	}
}

void GameObject::ChangeWait()
{
	if (state == StateType::WALK || state == StateType::RUN/* || state == StateType::JUMP || state == StateType::MAGIC || state == StateType::GUARD || state == StateType::RECEIVE*/)
	{
		state = StateType::WAIT;
	}

	if (velocity.y == 0 && state == StateType::JUMP)
	{
		//state = StateType::WAIT;
	}
	

}

void GameObject::ChangeWalkR()
{
	if ((state == StateType::WAIT || state == StateType::RUN))
	{
		state = StateType::WALK;
		isMirror = false;
	}
}

void GameObject::ChangeWalkL()
{
	if ((state == StateType::WAIT || state == StateType::RUN))
	{
		state = StateType::WALK;
		isMirror = true;
	}
}

void GameObject::ChangeRunR()
{
	if ((state == StateType::WAIT || state == StateType::WALK))
	{
		state = StateType::RUN;
		isMirror = false;
	}	
}

void GameObject::ChangeRunL()
{
	if ((state == StateType::WAIT || state == StateType::WALK))
	{
		state = StateType::RUN;
		isMirror = true;
	}
}

void GameObject::ChangeJump()
{
	if (state == StateType::WAIT || state == StateType::WALK || state == StateType::RUN)
	{
		state = StateType::JUMP;
	}
}

void GameObject::ChangeFalling()
{
	/*if (not isLanding)
	{
		state = StateType::FALLING;
	}*/
}

void GameObject::ChangeReceive()
{
	state = StateType::RECEIVE;
}

void GameObject::ChangeAttack()
{
	if (state == StateType::WAIT)
	{
		state = StateType::ATTACK;
	}
}



void GameObject::StateManagement()
{
	switch (state)
	{
	case StateType::WAIT:
		PatternLoop();
		WaitProcess();
		stateTypeNumber = 0;
		statename = {U"待機"};
		break;
	case StateType::WALK:
		PatternLoop();
		WalkProcess();
		stateTypeNumber = 1;
		statename = { U"歩き" };
		break;
	case StateType::RUN:
		PatternLoop();
		RunProcess();
		stateTypeNumber = 2;
		statename = { U"走り" };
		break;
	case StateType::JUMP:
		OnePattern();
		JumpProcess();
		stateTypeNumber = 3;
		statename = { U"ジャンプ" };
		break;
	case StateType::FALLING:
		PatternLoop();
		FallingProcess();
		stateTypeNumber = 4;
		statename = { U"滞空" };
		break;
	case StateType::LANDING:
		OnePattern();
		stateTypeNumber = 5;
		statename = { U"着地" };
		break;
	case StateType::RECEIVE:
		OnePattern();
		stateTypeNumber = 6;
		statename = { U"受け" };
		break;
	case StateType::ATTACK:
		OnePattern();
		stateTypeNumber = 7;
		statename = { U"攻撃" };
		break;
	case StateType::MAGIC:
		OnePattern();
		stateTypeNumber = 8;
		statename = { U"魔法" };
		break;
	case StateType::GUARD:
		stateTypeNumber = 9;
		statename = { U"ガード" };
		break;
	case StateType::NOTSTAMINA:
		stateTypeNumber = 10;
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
	font30(U"全体時間 ", animation[weaponTypeNumber][stateTypeNumber].motionTime * motionEndMagnification).draw(Scene::Width() - font30(U"全体時間 ", animation[weaponTypeNumber][stateTypeNumber].motionTime * motionEndMagnification).region().w, font30.height() * 2);
	font30(U"経過時間 ", animation[weaponTypeNumber][stateTypeNumber].elapsedTime).draw(Scene::Width() - font30(U"経過時間 ", animation[weaponTypeNumber][stateTypeNumber].elapsedTime).region().w, font30.height() * 3);
	font30(U"1枚あたりの時間 ", currentTime.ms()).draw(Scene::Width() - font30(U"1枚あたりの時間 ", currentTime.ms()).region().w, font30.height() * 4);
	font30(U"切り取り位置 ", animation[weaponTypeNumber][stateTypeNumber].cutPos).draw(Scene::Width() - font30(U"切り取り位置 ", animation[weaponTypeNumber][stateTypeNumber].cutPos).region().w, font30.height() * 5);

	if (speedChange == true)
	{
		font30(U"モーション終了倍率 ", motionEndMagnification).draw(Scene::Width() - font30(U"モーション終了倍率 ", motionEndMagnification).region().w, font30.height() * 6);

	}
}

void GameObject::playerCollsioninputoutdeg()
{
	textureSize = { position,animation[weaponTypeNumber][stateTypeNumber].texture.size() };

	if (MouseL.down())
	{

		if (clickCount < 2)
		{
			clickCount++;

			if (clickCount == 1)
			{
				firstPoint.center = Cursor::Pos();

			}
			else
			{
				secondRect = { firstPoint.center ,Cursor::Pos() - firstPoint.center };
			}
		}


	}

	if (MouseR.down())
	{
		if (clickCount > 0)
		{
			clickCount--;
		}
	}

}

void GameObject::playerCollsioninputoutdegDraw() const
{
	textureSize.drawFrame(3, Palette::Green);

	if (clickCount == 1)
	{
		firstPoint.draw(Palette::Red);
	}

	if (clickCount == 2)
	{
		secondRect.drawFrame(1, Palette::Blue);

	}

	font30(firstPoint.center - textureSize.pos, secondRect.size).draw(450, font30.height() * 2);

}

void GameObject::MotionEndMagnificationIncrease()
{
	speedChange = true;

	motionEndMagnification = motionEndMagnification * 2;
}

void GameObject::MotionEndMagnificationDecrease()
{
	speedChange = true;

	motionEndMagnification = motionEndMagnification / 2;
}


