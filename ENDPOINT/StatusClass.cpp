#include "stdafx.h"
#include "StatusClass.h"

void StatusClass::Reload(CSV statusData)
{
	for (int i = 1; i <= level; i++)
	{
		hitPoints = hitPoints + Parse<double>(statusData[1][i]);
		stamina = stamina + Parse<double>(statusData[2][i]);
		mental = mental + Parse<double>(statusData[3][i]);
		power = power + Parse<double>(statusData[4][i]);
		protection = protection + Parse<double>(statusData[5][i]);
		weight = weight + Parse<double>(statusData[6][i]);
		magicPoint = magicPoint + Parse<double>(statusData[8][i]);
		magicPower = magicPower + Parse<double>(statusData[9][i]);

		//現在値の更新(仮)
		currentHitPoints = hitPoints;
		currentStamina = stamina;
		currentMental = mental;
		currentMagicPoint = magicPoint;
	}
}

void StatusClass::StatusUpdate()
{
	switch (magicType)
	{
	case MagicType::NONE:
		magicTypeMame = { U"---" };
		break;
	case MagicType::FIREBALL:
		magicTypeMame = { U"火球" };
		break;
	case MagicType::THUNDER:
		magicTypeMame = { U"サンダー" };
		break;
	case MagicType::STATUSUP:
		magicTypeMame = { U"ステータスアップ" };
		break;
	case MagicType::HEEL:
		magicTypeMame = { U"ヒール" };
		break;
	case MagicType::TIME:
		magicTypeMame = { U"タイム" };
		break;
	default:
		break;
	}
}

void StatusClass::UIDraw()
{


}

void StatusClass::BaseStatusDrow()const
{
	font30(U"レベル ", level).draw(0, font30.height() * 0);
	font30(U"HP ", hitPoints).draw(0, font30.height()* 1);
	font30(U"スタミナ ", stamina).draw(0, font30.height() * 2);
	font30(U"精神力 ", mental).draw(0, font30.height() * 3);
	font30(U"攻撃力 ", power).draw(0, font30.height() * 4);
	font30(U"守備力 ", protection).draw(0, font30.height() * 5);
	font30(U"重量 ", weight).draw(0, font30.height() * 6);
	font30(U"魔法 ", magicTypeMame).draw(0, font30.height() * 7);
	font30(U"MP ", magicPoint).draw(0, font30.height() * 8);
	font30(U"魔力 ", magicPower).draw(0, font30.height() * 9);
}
