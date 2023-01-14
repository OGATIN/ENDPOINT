#pragma once

enum class StateType
{
	WAIT, WAIK, RUN, JUMP, RECEIVE, ATTACK,MAGIC, GUARD, NOTSTAMINA,
};

class AnimationClass
{
public:
	Texture waiting;

	Vec2 pos = {400,425};
	Rect cutPos = { 0,0,360,360 };

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
};

