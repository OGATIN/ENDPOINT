#pragma once
#include"Base.h"
#include"PlayerClass.h"
#include"EnemyClass.h"

const int mapData[25][48] =
{
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
	{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
	{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
	{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
	{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
	{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},

};


class Stage1 : public App::Scene
{
private:
	const int MapSize = 16;
	const Vec2 MapChipSize = { 32,32 };

	
    Texture BackScreen      { U"Material/3.MAP/6.町 背景.png" };
    Texture UnderGround     { U"Material/3.MAP/4.マップチップ.png" };

	Texture waitingMotionPNG	{ U"Material/1.img/プレイヤー/1.拳/1.待機モーション.png" };
	Texture walkMotionPNG		{ U"Material/1.img/プレイヤー/1.拳/2.歩きモーション.png" };
	Texture runMotionPNG		{ U"Material/1.img/プレイヤー/1.拳/3.ダッシュモーション.png" };
	Texture jumpMotionPNG		{ U"Material/1.img/プレイヤー/1.拳/4.ジャンプモーション.png" };
	Texture fallingMotionPNG	{ U"Material/1.img/プレイヤー/1.拳/5.空中モーション.png" };
	Texture landingMotionPNG	{ U"Material/1.img/プレイヤー/1.拳/6.着地モーション.png" };
	Texture receiveMotionPNG	{ U"Material/1.img/プレイヤー/1.拳/10.受けモーション.png" };
	Texture attackMotionPNG		{ U"Material/1.img/プレイヤー/1.拳/7.拳モーション.png" };
	Texture magicMotionPNG		{ U"Material/1.img/プレイヤー/1.拳/8.攻撃魔法モーション.png" };
	Texture guardMotionPNG		{ U"Material/1.img/プレイヤー/1.拳/11.防御モーション.png" };
	Texture notstaminaMotionPNG	{ U"Material/1.img/プレイヤー/1.拳/14.スタミナ切れ(待機).png" };

	Texture enemeyWaitingMotionPNG		{ U"Material/1.img/敵/1.拳/1.待機モーション-enemey.png" };
	Texture enemeyWalkMotionPNG			{ U"Material/1.img/敵/1.拳/2.歩きモーション-enemey.png" };
	Texture enemeyRunMotionPNG			{ U"Material/1.img/敵/1.拳/3.ダッシュモーション-enemey.png" };
	Texture enemeyJumpMotionPNG			{ U"Material/1.img/敵/1.拳/4.ジャンプモーション-enemey.png" };
	Texture enemeyFallingMotionPNG		{ U"Material/1.img/敵/1.拳/5.空中モーション-enemey.png" };
	Texture enemeyLandingMotionPNG		{ U"Material/1.img/敵/1.拳/6.着地モーション-enemey.png" };
	Texture enemeyReceiveMotionPNG		{ U"Material/1.img/敵/1.拳/10.受けモーション-enemey.png" };
	Texture enemeyAttackMotionPNG		{ U"Material/1.img/敵/1.拳/7.拳モーション-enemey.png" };
	Texture enemeyMagicMotionPNG		{ U"Material/1.img/敵/1.拳/8.攻撃魔法モーション-enemey.png" };
	Texture enemeyGuardMotionPNG		{ U"Material/1.img/敵/1.拳/11.防御モーション-enemey.png" };
	Texture enemeyNotstaminaMotionPNG	{ U"Material/1.img/敵/1.拳/14.スタミナ切れ(待機)-enemey.png" };

	

	CSV BasicStatData{ U"ConfigData/基礎ステータスデータ.csv" };
	CSV AnimationData{ U"ConfigData/アニメーションデータ.csv" };

	Texture playerPNG[4][20] =
	{
		/*0が拳*/{{waitingMotionPNG} ,{walkMotionPNG} ,{runMotionPNG},{jumpMotionPNG},{fallingMotionPNG},{landingMotionPNG},{receiveMotionPNG},{attackMotionPNG}},
		/*1が剣*/{},
		/*2が鈍器*/{},
		/*3が杖*/{},
		//各20種
	};

	Texture enemeyPNG[4][20] =
	{
		/*0が拳*/{{enemeyWaitingMotionPNG} ,{enemeyWalkMotionPNG} ,{enemeyRunMotionPNG},{enemeyJumpMotionPNG},{enemeyFallingMotionPNG},{enemeyLandingMotionPNG},{enemeyReceiveMotionPNG},{enemeyAttackMotionPNG}},
		/*1が剣*/{},
		/*2が鈍器*/{},
		/*3が杖*/{},
		//各20種
	};


	GameObject Player = { playerPNG ,AnimationData ,BasicStatData };

	EnemyClass Enemey = { enemeyPNG ,AnimationData ,BasicStatData };

	Vec2 cameraPos = {0,0};

	// プレイヤーインデックス (0 - 3)
	size_t playerIndex = 0;
	const Array<String> options = Range(1, 4).map([](int32 i) {return U"{}P"_fmt(i); });

	// デッドゾーンを有効にするか
	bool enableDeadZone = true;

	// 振動 (0.0 - 1.0)
	XInputVibration vibration;


	Font font{ 30 };


public:

    Stage1(const InitData& init)
        : IScene(init)
    {
        Initialize();
    }
    ~Stage1();

    void update() override;

    void draw() const override;

    void Initialize();//初期化

	void MapCollision(); //マップ用

	double HitBody(double velox1, double velox2);
};
