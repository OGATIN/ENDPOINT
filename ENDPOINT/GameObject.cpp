#include "stdafx.h"
#include "GameObject.h"


void GameObject::Reload(Texture _animation[4][20], Audio _audio[19], CSV AnimationData, CSV TextureShiftData, CSV statusData, CSV skillPointStatData, CSV experienceBorder, CSV magicSkillPointData, CSV magicOther)
{

	for (int j = 0; j < 4; j++)
	{
		for (int i = 0; i < 7; i++)
		{
			if (i < 5)
			{
				//とりあえず共通のデータはここでロード
				animation[j][i].Reload(_animation[j][i], AnimationData, i + 1);
			}
			else
			{
				switch (j)
				{
				case 0:

					if (i == (int)StateType::RECEIVE)
					{
						//とりあえず共通のデータはここでロード
						animation[j][i].Reload(_animation[j][i], AnimationData, 19);

					}

					if (i == (int)StateType::ATTACK)
					{
						//とりあえず共通のデータはここでロード
						animation[j][i].Reload(_animation[j][i], AnimationData, 7);
					}
					break;
				case 1:
					break;
				case 2:
					break;
				case 3:
					break;

				default:
					break;
				}

			}


		}
	}

	for (int i = 0; i < 19; i++)
	{
		audio[i] = _audio[i];
	}

	for (int j = 0; j < 4; j++)
	{
		for (int i = 0; i < 13; i++)
		{
			for (int p = 0; p < 11; p++)
			{
				shiftInternalHitRect[j][i][p] = /*Parse<Rect>(TextureShiftData[1][1])*/Parse<Rect>(TextureShiftData[(j * 10) + i + 1][p + 1]);
			}
			
		}
	}

	status.Reload(statusData, skillPointStatData, experienceBorder,magicSkillPointData, magicOther);
}

void GameObject::Update()
{
	//重力加算
	velocity.y += gravity;

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
	if (animation[(int)weapon][(int)state].cutPos.x >= animation[(int)weapon][(int)state].endPattern)
	{
		animation[(int)weapon][(int)state].ResetImage();
	}

}

void GameObject::OnePattern()
{
	if (animation[(int)weapon][(int)state].endPattern > animation[(int)weapon][(int)state].cutPos.x)
	{
		//タイル遷移
		if (currentTime.ms() > (animation[(int)weapon][(int)state].OnePatternMotionTime() * motionEndMagnification))
		{
			animation[(int)weapon][(int)state].cutPos.x++;
			currentTime.restart();
		}
	}

	//デバック用
	animation[(int)weapon][(int)state].elapsedTime = (animation[(int)weapon][(int)state].OnePatternMotionTime() * motionEndMagnification * animation[(int)weapon][(int)state].cutPos.x) + currentTime.ms();

}

bool GameObject::isOneLoop()
{
	return animation[(int)weapon][(int)state].cutPos.x >= animation[(int)weapon][(int)state].totalPatterns;
}

void GameObject::StateManagement()
{
	switch (state)
	{
	case StateType::WAIT:
		PatternLoop();
		WaitProcess();
		statename = { U"待機" };
		break;
	case StateType::WALK:
		PatternLoop();
		WalkProcess();
		statename = { U"歩き" };
		break;
	case StateType::RUN:
		PatternLoop();
		RunProcess();
		statename = { U"走り" };
		break;
	case StateType::JUMP:
		OnePattern();
		JumpProcess();
		statename = { U"ジャンプ" };
		break;
	case StateType::FALLING:
		PatternLoop();
		FallingProcess();
		statename = { U"滞空" };
		break;
	case StateType::RECEIVE:
		OnePattern();
		statename = { U"受け" };//未
		break;
	case StateType::ATTACK:
		OnePattern();
		//AttackProcess();
		statename = { U"攻撃" };//未
		break;
	case StateType::MAGIC:
		OnePattern();
		statename = { U"魔法" };//未
		break;
	case StateType::GUARD:
		statename = { U"ガード" };//未
		break;
	case StateType::NOTSTAMINA:
		statename = { U"スタミナ切れ" };//未
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

void GameObject::WaitProcess()
{
	if (velocity.x > 0)
	{
		velocity.x -= frictionForce;
	}
	else if (velocity.x < 0)
	{
		velocity.x += frictionForce;
	}

	AudioStop();

}

void GameObject::WalkProcess()
{
	//重量定義
	if (status.weight < charaSpeedMax)
	{
		charaSpeed = status.weight;
	}
	else
	{
		charaSpeed = charaSpeedMax;
	}

	//ベクトル加算
	if ((charaSpeed > velocity.x) && (-charaSpeed < velocity.x))
	{
		velocity.x += speedAdd;
	}

	if (velocity.x > 0)
	{
		isMirror = false;
	}

	if (velocity.x < 0)
	{
		isMirror = true;
	}


	if ((speedAdd == 0) || (charaSpeed < velocity.x) || (-charaSpeed > velocity.x))
	{
		if (velocity.x > 0 )
		{
			velocity.x -= frictionForce;
		}
		else if (velocity.x < 0)
		{
			velocity.x += frictionForce;
		}

	}

	if (velocity.x == 0)
	{
		audio[(int)SEstate::WAIKSE].stop();
		ChangeWait();
	}

	audio[(int)SEstate::WAIKSE].setVolume(GameData::MainVolume * GameData::SEVolume);
	audio[(int)SEstate::WAIKSE].play();
}

void GameObject::RunProcess()
{
 
	//重量定義
	if (status.weight < charaSpeedMax)
	{
		charaSpeed = status.weight * 1.5;
	}
	else
	{
		charaSpeed = charaSpeedMax * 1.5;
	}

	//ベクトル加算
	if ((charaSpeed > velocity.x) && (-charaSpeed < velocity.x))
	{
		velocity.x += speedAdd;
	}

	if (velocity.x > 0)
	{
		isMirror = false;
	}

	if (velocity.x < 0)
	{
		isMirror = true;
	}


	if (speedAdd == 0 || (charaSpeed < velocity.x) || (-charaSpeed > velocity.x))
	{
		if (velocity.x > 0)
		{
			velocity.x -= frictionForce;
		}
		else if (velocity.x < 0)
		{
			velocity.x += frictionForce;
		}

	}

	if (velocity.x == 0)
	{
		audio[(int)SEstate::RUNSE].stop();
		ChangeWait();
	}


	status.currentStamina -= (3.0 / 60.0);

	audio[(int)SEstate::RUNSE].setVolume(GameData::MainVolume * GameData::SEVolume);
	audio[(int)SEstate::RUNSE].play();
}

//要検討
void GameObject::JumpProcess()
{
	if (status.weight < jumpPowerMax)
	{
		jumpPower = -1 * (int)status.weight;
	}
	else
	{
		jumpPower = -1 * charaSpeedMax;
	}

	if (animation[(int)weapon][(int)state].cutPos.x == jumpTiming)
	{
		audio[(int)SEstate::JUMPSE].setVolume(GameData::MainVolume * GameData::SEVolume);
		audio[(int)SEstate::JUMPSE].stop();
		audio[(int)SEstate::JUMPSE].play();
	}

	if ((animation[(int)weapon][(int)state].cutPos.x >= jumpTiming) && (velocity.y > jumpPower))
	{
		velocity.y -= additionalAmount;
	}


	if (velocity.y <= jumpPower)
	{
		velocity.x += speedAdd;
		animation[(int)weapon][(int)state].ResetImage();
		isLanding = false;
		ChangeFalling();
	}	
}

void GameObject::FallingProcess()
{
	if (isLanding)
	{
		ChangeWait();
	}
}


//void GameObject::ReceiveProcess()
//{
//}
//

void GameObject::AttackProcess()
{
	if (isOneLoop())
	{
		state = StateType::WAIT;
	}

	switch (weapon)
	{
	case WeaponType::FIST:

		break;
	case WeaponType::SWORD:

		break;
	case WeaponType::HAMMER:

		break;
	case WeaponType::CANE:

		break;
	default:
		break;
	}
}

void GameObject::ChangeWait()
{
	if (state == StateType::WALK || state == StateType::RUN || state == StateType::FALLING)
	{
		state = StateType::WAIT;
	}
}

void GameObject::ChangeWalkR()
{
	if ((state == StateType::WAIT || state == StateType::WALK || state == StateType::RUN))
	{
		state = StateType::WALK;
		isMirror = false;
	}

	speedAdd = additionalAmount;

}

void GameObject::ChangeWalkL()
{
	if ((state == StateType::WAIT || state == StateType::WALK || state == StateType::RUN))
	{
		state = StateType::WALK;
		isMirror = true;
	}

	speedAdd = -additionalAmount;

}

void GameObject::ChangeRunR()
{
	if ((state == StateType::WAIT || state == StateType::WALK))
	{
		state = StateType::RUN;
		isMirror = false;
	}

	speedAdd = additionalAmount;
}

void GameObject::ChangeRunL()
{
	if ((state == StateType::WAIT || state == StateType::WALK))
	{
		state = StateType::RUN;
		isMirror = true;
	}

	speedAdd = -additionalAmount;
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
	if (not isLanding || state == StateType::JUMP)
	{
		state = StateType::FALLING;
	}
}

//
//void GameObject::ChangeReceive()
//{
//	state = StateType::RECEIVE;
//}
//
void GameObject::ChangeAttack()
{
	if (state == StateType::WAIT)
	{
		state = StateType::ATTACK;
	}
}



void GameObject::Draw() const
{
	animation[(int)weapon][(int)state].Draw(position,isMirror);
}

void GameObject::AudioStop()
{
	//ステイトが待機の時だけ音楽を止める->歩くから走るなどに遷移したとき音が止まらないと思われる
	//すべてのプロセスで自分の音以外を止める->コードクローンが増えすぎる
	//持続系のプロセスでそのプロセスでないなら停止するを毎フレーム読む
	//ステイトが切り替わったら前ステイトの音楽を停止する->プログラム的に不可能?前のステイトを記録しておく変数があれば可能かも？
	/*if (state == StateType::WAIT)
	{
		for (int i = 0; i < 19; i++)
		{
			audio[i].stop();
		}
	}*/

	audio[(int)SEstate::WAIKSE].stop();
	audio[(int)SEstate::RUNSE].stop();
	
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
}

void GameObject::StatusDraw() const
{
	font30(U"状態 ", statename).draw(Scene::Width() - font30(U"状態 ", statename).region().w, font30.height() * 0);
	font30(U"武器 ", weaponname).draw(Scene::Width() - font30(U"状態 ", weaponname).region().w, font30.height() * 1);
}


void GameObject::TimeDebuggDraw() const
{
	font30(U"全体時間 ", animation[(int)weapon][(int)state].motionTime * motionEndMagnification).draw(Scene::Width() - font30(U"全体時間 ", animation[(int)weapon][(int)state].motionTime * motionEndMagnification).region().w, font30.height() * 2);
	font30(U"経過時間 ", animation[(int)weapon][(int)state].elapsedTime).draw(Scene::Width() - font30(U"経過時間 ", animation[(int)weapon][(int)state].elapsedTime).region().w, font30.height() * 3);
	font30(U"1枚あたりの時間 ", currentTime.ms()).draw(Scene::Width() - font30(U"1枚あたりの時間 ", currentTime.ms()).region().w, font30.height() * 4);
	font30(U"切り取り位置 ", animation[(int)weapon][(int)state].cutPos).draw(Scene::Width() - font30(U"切り取り位置 ", animation[(int)weapon][(int)state].cutPos).region().w, font30.height() * 5);

}

void GameObject::CoordinateRelated() const
{
	font30(U"画面座標", position).draw(0, font30.height() * 0);
	font30(U"ベクトル", velocity).draw(0, font30.height() * 1);
	font30(U"スピード", charaSpeed).draw(0, font30.height() * 2);
	font30(U"ジャンプパワー ", jumpPower).draw(0, font30.height() * 3);
	font30(U"着地してるか ", isLanding).draw(0, font30.height() * 4);
}




