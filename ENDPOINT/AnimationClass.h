#pragma once

enum class StateType
{
	WAIT, WAIK, RUN, JUMP, RECEIVE, ATTACK,MAGIC, GUARD, NOTSTAMINA,
};

class AnimationClass
{
public:
	Texture waiting;
	Texture texture;

	Rect cutPos = { 0,0,360,360 };

	Rect waitPosDifference = { 62,30,35,130 };

	Stopwatch currentTime;

	double activeTime = 0;		//持続時間(秒),技の当たり判定がある時間

	double recoveryTime = 0;	//後隙(硬直)時間(秒),技の当たり判定がない時間

	double attackTechnique = 0; //全体時間(秒),持続と後隙の合計,技の総時間

	double motionTime = 0;		//モーション時間(秒),当たり判定のある時間などを考慮せず1モーションが終わるまでの時間

	int animationPattern = 0;	//総パターン数,1モーションで使うパターンの総数

	int startPattern = 0;		//切り取り位置(始)

	int endPattern = 0;			//切り取り位置(終)

	int widthSize = 0;

	int heightSize = 0;

	//デバック用フォント
	Font font30{ 30 };

	AnimationClass(){};
	AnimationClass(Texture wait)
	{
		waiting = wait;
	};

	AnimationClass(Texture _texture,CSV animationData, int currentMotion)
	{
		texture				= _texture;
		activeTime			= activeTime		+ Parse<double>(animationData[currentMotion][1]);
		recoveryTime		= recoveryTime		+ Parse<double>(animationData[currentMotion][2]);
		attackTechnique		= attackTechnique	+ Parse<double>(animationData[currentMotion][3]);
		motionTime			= motionTime		+ Parse<double>(animationData[currentMotion][5]);
		animationPattern	= animationPattern	+ Parse<int>   (animationData[currentMotion][6]);
		startPattern		= startPattern		+ Parse<int>   (animationData[currentMotion][7]);
		endPattern			= endPattern		+ Parse<int>   (animationData[currentMotion][8]);

		texture.width() / widthSize;
		texture.height() / heightSize;
	};


 	void Reload(Texture wait);/*CSV AnimationData*/
	void TimeDrow()const;
	void Wait();
	void WaitDraw(Vec2 position)const;
};

