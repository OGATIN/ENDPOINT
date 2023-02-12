#include "stdafx.h"
#include "GameObject.h"


void GameObject::Reload(Texture _animation[4][20], EffectClass effect[2], Audio _audio[19], CSV AnimationData, CSV TextureShiftData, CSV statusData, CSV skillPointStatData, CSV experienceBorder, CSV magicSkillPointData, CSV magicOther)
{

	for (int j = 0; j < 4; j++)
	{
		for (int i = 0; i < 8; i++)
		{
			if (i < 6)
			{
				//とりあえず共通のデータはここでロード
				animation[j][i].Load(_animation[j][i], AnimationData, i + 1);
			}
			else
			{
				switch (j)
				{
				case 0:

					if (i == (int)StateType::ATTACK)
					{
						//とりあえず共通のデータはここでロード
						animation[j][i].Load(_animation[j][i], AnimationData, 7,true);
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



			if (i == (int)StateType::MAGIC)
			{
				//とりあえず共通のデータはここでロード
				animation[j][7].Load(_animation[j][7], AnimationData, 11);
				int a = 0;
			}

		}
	}

	for (int i = 0; i < 2; i++)
	{
		Effects[i] = effect[i];
	}

	for (int i = 0; i < 19; i++)
	{
		audio[i] = _audio[i];
	}

	for (int j = 0; j < 1; j++)
	{
		for (int i = 0; i < 8; i++)
		{
			for (int p = 0; p < animation[j][i].totalPatterns; p++)
			{
				shiftInternalHitRect[j][i][p] = /*Parse<Rect>(TextureShiftData[1][1])*/Parse<Rect>(TextureShiftData[(j * 14) + i + 1][p + 1]);
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
	if (animation[(int)status.weapon][(int)state].cutPos.x >= animation[(int)status.weapon][(int)state].totalPatterns)
	{
		animation[(int)status.weapon][(int)state].ResetImage();
	}

}

void GameObject::OnePattern()
{
	if (animation[(int)status.weapon][(int)state].totalPatterns > animation[(int)status.weapon][(int)state].cutPos.x)
	{
		//タイル遷移
		if (currentTime.ms() > (animation[(int)status.weapon][(int)state].OnePatternMotionTime() * motionEndMagnification))
		{
			animation[(int)status.weapon][(int)state].cutPos.x++;
			currentTime.restart();
		}
	}

	//デバック用
	animation[(int)status.weapon][(int)state].elapsedTime = (animation[(int)status.weapon][(int)state].OnePatternMotionTime() * motionEndMagnification * animation[(int)status.weapon][(int)state].cutPos.x) + currentTime.ms();

}

void GameObject::EffectAdd(EffectType effectType,Vec2 addpos)
{
	Effects[(int)effectType].EffectTypeChange(effectType, status.subSkill, status.specialFunctioVernValue);
	Effects[(int)effectType].CreationPosChange(addpos);
	Effects[(int)effectType].MirrorChange(isMirror);

	effects << Effects[(int)effectType];
}

void GameObject::EffectUpdate()
{
	for (auto& _effects : effects)
	{
		_effects.Update();
	}

	effects.remove_if([](EffectClass effect) { return effect.effectBase.motionTime <= effect.currentTime.ms(); });

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
		ReceiveProcess();
		statename = { U"受け" };
		break;
	case StateType::ATTACK:
		AttackProcess();
		statename = { U"攻撃" };
		break;
	case StateType::MAGIC:

		statename = { U"魔法" };

		switch (status.magicType)
		{
		case MagicType::NONE:
			ChangeWait();
			break;
		case MagicType::FIREBALL:
			OnePattern();
			MagicProcess();
			break;
		case MagicType::THUNDER:
			break;
		case MagicType::STATUSUP:
			break;
		case MagicType::HEAL:
			break;
		case MagicType::TIME:
			break;
		default:
			break;
		}

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

	switch (status.weapon)
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

	if (animation[(int)status.weapon][(int)state].cutPos.x == jumpTiming)
	{
		audio[(int)SEstate::JUMPSE].setVolume(GameData::MainVolume * GameData::SEVolume);
		audio[(int)SEstate::JUMPSE].stop();
		audio[(int)SEstate::JUMPSE].play();
	}

	if ((animation[(int)status.weapon][(int)state].cutPos.x >= jumpTiming) && (velocity.y > jumpPower))
	{
		velocity.y -= additionalAmount;
	}


	if (velocity.y <= jumpPower)
	{
		velocity.x += speedAdd;
		animation[(int)status.weapon][(int)state].ResetImage();
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

void GameObject::ReceiveProcess()
{

	if (velocity.x > 0)
	{
		velocity.x -= frictionForce;
	}
	else if (velocity.x < 0)
	{
		velocity.x += frictionForce;
	}

	if (isOneLoop())
	{
		animation[(int)status.weapon][(int)state].cutPos.x = 0;
		ChangeWait();
	}
}

void GameObject::AttackProcess()
{
	EffectUpdate();

	switch (status.weapon)
	{
	case WeaponType::FIST:
		FistHandling();
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

void GameObject::FistHandling()
{
	if (velocity.x > 0)
	{
		velocity.x -= frictionForce;
	}
	else if (velocity.x < 0)
	{
		velocity.x += frictionForce;
	}

	if (currentTime.ms() >= 0 && currentTime.ms() < 60)
	{
		animation[(int)status.weapon][(int)state].cutPos.x = 0;
		
	}
	else if (currentTime.ms() > 60 && currentTime.ms() < 120)
	{
		animation[(int)status.weapon][(int)state].cutPos.x = 1;
	}
	else if (currentTime.ms() > 120 && currentTime.ms() < 180)
	{
		animation[(int)status.weapon][(int)state].cutPos.x = 2;
	}
	else if (currentTime.ms() > 180 && currentTime.ms() < 300)
	{
		if (isRearGap == false)
		{
			if (isMirror == false)
			{
				EffectAdd(EffectType::FISTEFFECT,position + fistFiringPoint);
			}
			else
			{
				EffectAdd(EffectType::FISTEFFECT,position + fistFiringMirrorPoint);
			}

			audio[(int)SEstate::FISTSE].setVolume(GameData::MainVolume * GameData::SEVolume);
			audio[(int)SEstate::FISTSE].stop();
			audio[(int)SEstate::FISTSE].play();
			isRearGap = true;
		}

		animation[(int)status.weapon][(int)state].cutPos.x = 3;
	}
	else if (currentTime.ms() > 300 && currentTime.ms() < 384)
	{
		animation[(int)status.weapon][(int)state].cutPos.x = 4;
	}
	else if (currentTime.ms() > 384 && currentTime.ms() < 468)
	{
		animation[(int)status.weapon][(int)state].cutPos.x = 5;
	}
	else if (currentTime.ms() > 468 && currentTime.ms() < animation[(int)status.weapon][(int)state].motionTime)
	{
		animation[(int)status.weapon][(int)state].cutPos.x = 6;
	}
	else
	{
		isRearGap = false;
		animation[(int)status.weapon][(int)state].ResetImage();
		ChangeWait();
	}

}

void GameObject::MagicProcess()
{
	if (velocity.x > 0)
	{
		velocity.x -= frictionForce;
	}
	else if (velocity.x < 0)
	{
		velocity.x += frictionForce;
	}

	if (animation[(int)status.weapon][(int)state].cutPos.x >= 4)
	{
		if (isRearGap == false)
		{
			if (isMirror == false)
			{
				EffectAdd(EffectType::FIREBALLEFFECT, position + fistFiringPoint);
			}
			else
			{
				EffectAdd(EffectType::FIREBALLEFFECT, position + fistFiringMirrorPoint);
			}

			audio[(int)SEstate::FIREBALLSE].setVolume(GameData::MainVolume * GameData::SEVolume);
			audio[(int)SEstate::FIREBALLSE].stop();
			audio[(int)SEstate::FIREBALLSE].play();
			isRearGap = true;
		}
	}

	if (isOneLoop())
	{

		isRearGap = false;
		animation[(int)status.weapon][(int)state].ResetImage();
		ChangeWait();
	}
}

void GameObject::ChangeWait()
{
	if (state == StateType::WALK || state == StateType::RUN || state == StateType::FALLING || state == StateType::RECEIVE || state == StateType::ATTACK || state == StateType::MAGIC)
	{
		state = StateType::WAIT;
		currentTime.restart();

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
		currentTime.restart();
	}
}

void GameObject::ChangeFalling()
{
	if (not isLanding || state == StateType::JUMP)
	{
		state = StateType::FALLING;
	}
}

void GameObject::ChangeReceive(Vec2 knockBack)
{
	velocity += knockBack;
	state = StateType::RECEIVE;

	audio[(int)SEstate::DAMAGESE].setVolume(GameData::MainVolume * GameData::SEVolume);
	audio[(int)SEstate::DAMAGESE].stop();
	audio[(int)SEstate::DAMAGESE].play();
	currentTime.restart();
}

void GameObject::ChangeAttack()
{
	if (state == StateType::WAIT || state == StateType::WALK || state == StateType::RUN || state == StateType::FALLING )
	{
		state = StateType::ATTACK;
		currentTime.restart();

	}
}

void GameObject::ChangeAttackMagic()
{
	if (state == StateType::WAIT || state == StateType::WALK || state == StateType::RUN || state == StateType::FALLING)
	{
		state = StateType::MAGIC;
		currentTime.restart();

	}
}

void GameObject::Draw() const
{
	animation[(int)status.weapon][(int)state].Draw(position,isMirror);
}

void GameObject::EffectDraw(bool hitBoxDraw) const
{
	for (const auto& _effects : effects)
	{
		_effects.Draw();;

		if (hitBoxDraw == true)
		{
			_effects.hitBox.drawFrame();
		}
	}

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
	font30(U"全体時間 ", animation[(int)status.weapon][(int)state].motionTime * motionEndMagnification).draw(Scene::Width() - font30(U"全体時間 ", animation[(int)status.weapon][(int)state].motionTime * motionEndMagnification).region().w, font30.height() * 2);
	font30(U"経過時間 ", animation[(int)status.weapon][(int)state].elapsedTime).draw(Scene::Width() - font30(U"経過時間 ", animation[(int)status.weapon][(int)state].elapsedTime).region().w, font30.height() * 3);
	font30(U"1枚あたりの時間 ", currentTime.ms()).draw(Scene::Width() - font30(U"1枚あたりの時間 ", currentTime.ms()).region().w, font30.height() * 4);
	font30(U"切り取り位置 ", animation[(int)status.weapon][(int)state].cutPos).draw(Scene::Width() - font30(U"切り取り位置 ", animation[(int)status.weapon][(int)state].cutPos).region().w, font30.height() * 5);

}

void GameObject::CoordinateRelated() const
{
	font30(U"画面座標", position).draw(0, font30.height() * 0);
	font30(U"ベクトル", velocity).draw(0, font30.height() * 1);
	font30(U"スピード", charaSpeed).draw(0, font30.height() * 2);
	font30(U"ジャンプパワー ", jumpPower).draw(0, font30.height() * 3);
	font30(U"着地してるか ", isLanding).draw(0, font30.height() * 4);
	font30(U"プレイヤーからのマウス地点 ", Cursor::Pos() - position).draw(0, font30.height() * 5);

}

void GameObject::EffectsDraw() const
{
	for (int i = 0; i < effects.size(); i++)
	{
		font30(effects[i].currentTime.ms()).draw(0, font30.height() * i);
	}
}




