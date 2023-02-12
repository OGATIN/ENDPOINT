#include "stdafx.h"
#include "EnemyClass.h"

void EnemyClass::Update()
{
	gameObject.Update();

	gameObject.position += gameObject.velocity;

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

void EnemyClass::TestAI(Vec2 pos)
{
	

}

//拳
void EnemyClass::Fist(GameObject Player)
{
	Update();

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
	
	gameObject.animation[(int)gameObject.status.weapon][(int)gameObject.state].Draw(gameObject.position - localCameraPos, gameObject.isMirror);
}


/*デバック表示*/

void EnemyClass::DebugDraw() const
{
	gameObject.GetHitRect().drawFrame(2, Palette::Red);


	sR.draw(ColorF(255, 255, 0, 0.4));
	aR.draw(ColorF(0, 255, 0, 0.4));
}
