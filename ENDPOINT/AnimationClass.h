#pragma once

enum class StateType
{
	WAIT, WAIK, RUN, JUMP, RECEIVE, ATTACK,MAGIC, GUARD, NOTSTAMINA,
};

class AnimationClass
{
public:
	Texture waiting;

	Rect cutPos = { 0,0,360,360 };

	Rect waitPosDifference = { 62,30,35,130 };

	Stopwatch currentTime;

	int animationPattern;

	//デバック用フォント
	Font font30{ 30 };

	AnimationClass(){};
	AnimationClass(Texture wait)
	{
		waiting = wait;
	};

	//AnimationClass(CSV animationData)
	//{
	//	for (int i = 1; i <= animationPattern; i++)
	//	{
	//		hitPoints = hitPoints + Parse<double>(statusData[1][i]);
	//		stamina = stamina + Parse<double>(statusData[2][i]);
	//		mental = mental + Parse<double>(statusData[3][i]);
	//		power = power + Parse<double>(statusData[4][i]);
	//		protection = protection + Parse<double>(statusData[5][i]);
	//		weight = weight + Parse<double>(statusData[6][i]);
	//		magicPoint = magicPoint + Parse<double>(statusData[8][i]);
	//		magicPower = magicPower + Parse<double>(statusData[9][i]);
	//	}
	//};

 	void Reload(Texture wait);/*CSV AnimationData*/
	void TimeDrow()const;
	void Wait();
	void WaitDraw(Vec2 position)const;
};

