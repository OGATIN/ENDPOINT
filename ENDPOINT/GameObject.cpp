#include "stdafx.h"
#include "GameObject.h"


void GameObject::Reload(Texture _animation[4][20], Audio _audio[19], CSV AnimationData, CSV TextureShiftData, CSV statusData, CSV skillPointStatData, CSV experienceBorder, CSV magicSkillPointData, CSV magicOther)
{

	for (int j = 0; j < 4; j++)
	{
		for (int i = 0; i < 7; i++)
		{
			//とりあえず共通のデータはここでロード
			animation[j][i].Reload(_animation[j][i], AnimationData, i + 1);
		}
	}

	for (int i = 0; i < 19; i++)
	{
		audio[i] = _audio[i];
	}

	for (int j = 0; j < 55; j++)
	{
		for (int i = 0; i < 10; i++)
		{
			//shiftInternalHitRect[0][0] = Parse<Rect>(TextureShiftData[j+1][i+1]);
		}
	}
	shiftInternalHitRect[0][0] = Parse<Rect>(TextureShiftData[1][1]);
	shiftInternalHitRect[0][1] = Parse<Rect>(TextureShiftData[1][1]);

	status.Reload(statusData, skillPointStatData, experienceBorder,magicSkillPointData, magicOther);
}

void GameObject::Update()
{

	//重力加算
	velocity.y += gravity;

	//重量定義
	if (status.weight < jumpPowerMax)
	{
		jumpPower = (int)status.weight;
	}
	else
	{
		jumpPower = charaSpeedMax;
	}

	
	//Xベクトル減少
	if (state != StateType::FALLING && state != StateType::JUMP)
	{
		if (charaSpeed > 0)
		{
			charaSpeed -= 1;
		}
	}

	if (state == StateType::JUMP)
	{
		if (charaSpeed > 0)
		{
			charaSpeed -= 0.1;
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
	if (animation[(int)weapon][(int)state].cutPos.x >= animation[(int)weapon][(int)state].endPattern)
	{
		animation[(int)weapon][(int)state].cutPos.x = animation[(int)weapon][(int)state].startPattern;

		animation[(int)weapon][(int)state].elapsedTime = 0;
	}

	//デバック用
	animation[(int)weapon][(int)state].elapsedTime = (animation[(int)weapon][(int)state].OnePatternMotionTime() * motionEndMagnification * animation[(int)weapon][(int)state].cutPos.x) + currentTime.ms();
}

void GameObject::OnePattern()
{
	//タイル遷移
	if (currentTime.ms() > (animation[(int)weapon][(int)state].OnePatternMotionTime() * motionEndMagnification))
	{
		animation[(int)weapon][(int)state].cutPos.x++;
		currentTime.restart();
	}
}

bool GameObject::isOneLoop()
{
	return animation[(int)weapon][(int)state].cutPos.x >= animation[(int)weapon][(int)state].endPattern;
}

void GameObject::WaitProcess()
{
	velocity.x = 0;
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

	//反転してる向きに応じて処理
	if (isMirror)
	{
		velocity.x = - charaSpeed;
	}
	else
	{
		velocity.x =  charaSpeed;
	}
	audio[1].setVolume(GameData::MainVolume * GameData::SEVolume);
	audio[1].play();
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

	//反転してる向きに応じて処理
	if (isMirror)
	{
		velocity.x = - charaSpeed;
	}
	else
	{
		velocity.x = charaSpeed;
	}

	status.currentStamina -= (3.0 / 60.0);

	audio[2].setVolume(GameData::MainVolume * GameData::SEVolume);
	audio[2].play();
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
	if (state == StateType::WALK || state == StateType::RUN)
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
		audio[3].playOneShot(GameData::MainVolume * GameData::SEVolume);
		status.currentStamina -= 5;
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
	audio[4].playOneShot(GameData::MainVolume * GameData::SEVolume);
}



void GameObject::StateManagement()
{
	switch (state)
	{
	case StateType::WAIT:
		PatternLoop();
		WaitProcess();
		statename = {U"待機"};
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
	case StateType::LANDING:
		OnePattern();
		statename = { U"着地" };
		break;
	case StateType::RECEIVE:
		OnePattern();
		statename = { U"受け" };
		break;
	case StateType::ATTACK:
		OnePattern();
		statename = { U"攻撃" };
		break;
	case StateType::MAGIC:
		OnePattern();
		statename = { U"魔法" };
		break;
	case StateType::GUARD:
		statename = { U"ガード" };
		break;
	case StateType::NOTSTAMINA:
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

	if (state != StateType::WALK)
	{
		audio[1].stop();
	}
	if (state != StateType::RUN)
	{
		audio[2].stop();
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
	font30(U"全体時間 ", animation[(int)weapon][(int)state].motionTime * motionEndMagnification).draw(Scene::Width() - font30(U"全体時間 ", animation[(int)weapon][(int)state].motionTime * motionEndMagnification).region().w, font30.height() * 2);
	font30(U"経過時間 ", animation[(int)weapon][(int)state].elapsedTime).draw(Scene::Width() - font30(U"経過時間 ", animation[(int)weapon][(int)state].elapsedTime).region().w, font30.height() * 3);
	font30(U"1枚あたりの時間 ", currentTime.ms()).draw(Scene::Width() - font30(U"1枚あたりの時間 ", currentTime.ms()).region().w, font30.height() * 4);
	font30(U"切り取り位置 ", animation[(int)weapon][(int)state].cutPos).draw(Scene::Width() - font30(U"切り取り位置 ", animation[(int)weapon][(int)state].cutPos).region().w, font30.height() * 5);

	if (speedChange == true)
	{
		font30(U"モーション終了倍率 ", motionEndMagnification).draw(Scene::Width() - font30(U"モーション終了倍率 ", motionEndMagnification).region().w, font30.height() * 6);

	}

	if (frameNumber == true)
	{
		font30(U"終了番号 ", animation[(int)weapon][(int)state].endPattern).draw(Scene::Width() - font30(U"終了番号 ", animation[(int)weapon][(int)state].endPattern).region().w, font30.height() * 6);
		font30(U"現在の番号 ", animation[(int)weapon][(int)state].cutPos.x).draw(Scene::Width() - font30(U"現在の番号 ", animation[(int)weapon][(int)state].cutPos.x).region().w, font30.height() * 7);
	}
}

void GameObject::playerCollsioninputoutdeg()
{
	textureSize = { position,animation[(int)weapon][(int)state].texture.size() };

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

void GameObject::MotionFrameSkip()
{
	frameNumber = true;

	animation[(int)weapon][(int)state].cutPos.x++;

}

void GameObject::MotionFrameBack()
{
	frameNumber = true;

	animation[(int)weapon][(int)state].cutPos.x--;

	if (animation[(int)weapon][(int)state].cutPos.x < animation[(int)weapon][(int)state].startPattern)
	{
		animation[(int)weapon][(int)state].cutPos.x = animation[(int)weapon][(int)state].endPattern - 1;
	}

}



