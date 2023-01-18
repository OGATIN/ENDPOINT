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

	int widthSize = 0;			//画像一枚の横幅

	int heightSize = 0;			//画像一枚の縦幅

	int currentPattern = 0;	//現在選択してるタイル

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
		activeTime			= Parse<double>(animationData[currentMotion][1]);
		recoveryTime		= Parse<double>(animationData[currentMotion][2]);
		attackTechnique		= Parse<double>(animationData[currentMotion][3]);
		motionTime			= Parse<double>(animationData[currentMotion][5]);
		animationPattern	= Parse<int>   (animationData[currentMotion][6]);

		Initialize();
	};

	
	/// @brief 初期定義
	void Initialize();

	//bool isNotAnimation();

	/// @brief １パターンあたりの時間を求める
	/// @return １パターンあたりの時間
	double OnePatternMotionTime();

	/// @brief 画像一枚の縦幅と横幅をセット
	void TextureWidthHeightSet();

	/// @brief startPatternとendPatternをセット
	void PatternSet();

	void PatternLoop();


	//void Reload(Texture wait);/*CSV AnimationData*/
	//void TimeDrow()const;
	//void Wait();
	//void WaitDraw(Vec2 position)const;
};

