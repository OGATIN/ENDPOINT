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


void EnemyClass::Draw()const
{
	gameObject.Draw();
}

void EnemyClass::DebugDraw() const
{
	gameObject.GetHitRect().drawFrame(2, Palette::Red);
}
