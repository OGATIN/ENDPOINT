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

	//デバック用フォント
	Font font30{ 30 };

	AnimationClass(){};
	AnimationClass(Texture wait)
	{
		waiting = wait;
	};

 	void Reload(Texture wait);/*CSV AnimationData*/
	void TimeDrow();
	void Wait();
	void WaitDraw(Vec2 position)const;
};

