#include "stdafx.h"
#include "EnemyClass.h"

void EnemyClass::Initialize(Vec2 generationPos)
{
	gameObject.status.weight = 3;
	if (Random<int>(1) == 0)
	{
		gameObject.status.weapon = WeaponType::FIST;

	}
	else
	{
		gameObject.status.weapon = WeaponType::SWORD;

	}
	gameObject.MapPosition = generationPos;

}

void EnemyClass::Update()
{
	gameObject.MotionStart();

	gameObject.Update();

	gameObject.screenPosition.y += gameObject.velocity.y;
	gameObject.MapPosition.x += gameObject.velocity.x;

	gameObject.screenPosition.x = gameObject.MapPosition.x - GameData::cameraPos.x;


}

void EnemyClass::AIManegement(GameObject Player)
{
	Update();

	switch (gameObject.status.weapon)
	{
	case WeaponType::FIST:
		Fist(Player);
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

void EnemyClass::TestAI(Vec2 mapPos)
{
	if (gameObject.state != StateType::RECEIVE)
	{
		if ((mapPos.x + AIspace) <= gameObject.ObjectCenterWorldPoint().x)
		{
			gameObject.ChangeWalkL();
		}
		else if (gameObject.ObjectCenterWorldPoint().x <= (mapPos.x - AIspace))
		{
			gameObject.ChangeWalkR();
		}
		else
		{
			gameObject.ChangeWait();
		}

	}

}

//拳
void EnemyClass::Fist(GameObject Player)
{

	//索敵
	if (sR.intersects(Player.hitBox))
	{
		if (Player.hitBox.x > gameObject.hitBox.x)
		{
			gameObject.state = StateType::WALK;
			gameObject.isMirror = true;
		}
		else
		{
			gameObject.state = StateType::WALK;
			gameObject.isMirror = false;
		}
	}
	else
	{

	}


	/*
	if (攻撃範囲に入っていなかったら)
	{
		//
	}
	else
	{
		if (.intersects(Player.hitBox))
		{
			if (Player.hitBox.x > gameObject.hitBox.x)
			{
				gameObject.state = StateType::WALK;
				gameObject.isMirror = true;
			}
			else
			{
				gameObject.state = StateType::WALK;
				gameObject.isMirror = false;
			}
		}
		else
		{

		}
	}
	*/


}




