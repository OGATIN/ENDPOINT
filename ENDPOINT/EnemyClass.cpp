#include "stdafx.h"
#include "EnemyClass.h"

void EnemyClass::TestAI(Vec2 pos)
{
	gameObject.Update();
	gameObject.StateManagement();
	gameObject.MotionStart();

	gameObject.ChangeWait();

	int PosL = gameObject.GetLeft();
	int PosR = gameObject.GetRight();
	int PosT = gameObject.GetTop();
	int PosB = gameObject.GetBottom();

	if (pos.x <= PosL)
	{
		gameObject.ChangeWalkL();
	}
	if (PosR <= pos.x)
	{
		gameObject.ChangeWalkR();
	}


}

void EnemyClass::AIManegement()
{
}


//拳
void EnemyClass::Fist(GameObject Player)
{
	gameObject.Update();

	gameObject.position += gameObject.velocity;

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
	
	gameObject.Draw();
}

void EnemyClass::DebugDraw() const
{
	gameObject.GetHitRect().drawFrame(2, Palette::Red);
	sR.draw(ColorF(255, 255, 0, 0.4));
	aR.draw(ColorF(0, 255, 0, 0.4));
}
