#pragma once

enum class MagicType
{
	NONE,FIREBALL, THUNDER, STATUSUP,HEEL,TIME,
};

class StatusClass
{
public:

	int level = 1;//プレイヤーのレベル

	double hitPoints = 0;//HP
	double stamina = 0;//スタミナ
	double mental = 0;//精神力
	double power = 0;//攻撃力
	double protection = 0;//防御力
	double weight = 0;//重量
	MagicType magicType = MagicType::NONE;//魔法の種類
	double magicPoint = 0;//MP
	double magicPower = 0;//魔力

	//魔法名表示用
	String magicTypeMame;

	//デバック用フォント
	Font font30{ 30 };

	StatusClass() {};

	StatusClass(CSV statusData)
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
		}
	};


	void Reload(CSV statusData);

	void StatusUpdate();
	void DaseStatusDrow()const;
};

