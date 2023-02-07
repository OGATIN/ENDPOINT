#include "stdafx.h"
#include "EnemyClass.h"

void EnemyClass::Update(Vec2 camerapos)
{
	gameObject.Update();

	gameObject.position += gameObject.velocity;

	localCameraPos = camerapos;

}

void EnemyClass::AIManegement(Vec2 camerapos,GameObject Player)
{
	Update(camerapos);

	switch (gameObject.weapon)
	{
	case WeaponType::FIST:
		Fist(Player, camerapos);
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

void EnemyClass::TestAI(Vec2 camerapos,Vec2 pos)
{
	//Update(camerapos);

	//gameObject.StateManagement();
	//gameObject.MotionStart();

	//gameObject.ChangeWait();

	//int PosL = gameObject.GetLeft();
	//int PosR = gameObject.GetRight();
	//int PosT = gameObject.GetTop();
	//int PosB = gameObject.GetBottom();

	//if (pos.x <= PosL)
	//{
	//	gameObject.ChangeWalkL();
	//}
	//if (PosR <= pos.x)
	//{
	//	gameObject.ChangeWalkR();
	//}


}

//拳
void EnemyClass::Fist(GameObject Player,  Vec2 camerapos)
{
	Update(camerapos);

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




void EnemyClass::Draw()const
{
	
	gameObject.animation[(int)gameObject.weapon][(int)gameObject.state].Draw(gameObject.position - localCameraPos, gameObject.isMirror);
}


/*デバック表示*/

void EnemyClass::DebugDraw() const
{
	gameObject.GetHitRect().drawFrame(2, Palette::Red);


	sR.draw(ColorF(255, 255, 0, 0.4));
	aR.draw(ColorF(0, 255, 0, 0.4));
}
