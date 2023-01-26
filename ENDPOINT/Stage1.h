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

	double HitBodyVelocity(double velox1, double velox2)
	{
		//返す値は結果のベクトル

		//現在の向きを確認
		bool _1PRight = velox1 > 0;
		bool _1PLeft = velox1 < 0;
		bool _1PStop = velox1 == 0;

		bool _2PRight = velox2 > 0;
		bool _2PLeft = velox2 < 0;
		bool _2PStop = velox2 == 0;

		//ベクトルの大きさを定義
		double _1PVeloSize = velox1;
		double _2PVeloSize = velox2;
		//大きさが-なら+に変換して扱いやすくする
		if (velox1 < 0)_1PVeloSize *= -1;
		if (velox2 < 0)_2PVeloSize *= -1;

		//どっちが押してるかを判断
		bool is1PPush = false;
		bool is2PPush = false;
		bool isSame = false;

		//フラグを立てる
		if (_1PVeloSize > _2PVeloSize)
		{
			is1PPush = true;
		}
		else if (_2PVeloSize > _1PVeloSize)
		{
			is2PPush = true;
		}
		else if (_1PVeloSize == _2PVeloSize)
		{
			isSame = true;
		}

		//両方同じ方向に進んでる時の速度差による衝突(両方右向にき進んでる+/+ || 両方左向きに進んでる-/-)
		if (_1PRight == true && _2PRight == true || _1PLeft == true && _2PLeft == true)
		{
			if (is1PPush)return velox1;

			if (is2PPush)return velox2;
		}

		//お互いに違う向きでの衝突(1Pは右向きの衝突+/- || 1Pは左向きの衝突-/+)
		if (_1PRight == true && _2PLeft == true || _1PLeft == true && _2PRight == true)
		{
			//符号がお互い違うので足す
			if (is1PPush)return velox1 + velox2;

			if (is2PPush)return velox2 + velox1;
		}

		//1Pが動いてて2Pが停止+or-/0
		if ((_1PLeft || _1PRight) && _2PStop)
		{
			return velox1;
		}

		//2Pが動いてて1Pが停止0/+or-
		if ((_2PLeft || _2PRight) && _1PStop)
		{
			return velox2;
		}

		//両方同じベクトル量だった時(衝突もしくは停止)
		if (isSame)
		{
			return 0;
		}
	}

	bool Is1PPush(double velox1, double velox2)
	{
		//ベクトルの大きさを定義
		double _1PVeloSize = velox1;
		double _2PVeloSize = velox2;
		//大きさが-なら+に変換して扱いやすくする
		if (velox1 < 0)_1PVeloSize *= -1;
		if (velox2 < 0)_2PVeloSize *= -1;

		//どっちが押してるかを判断
		bool is1PPush = false;

		//フラグを立てる
		if (_1PVeloSize > _2PVeloSize)is1PPush = true;
		else if (_2PVeloSize > _1PVeloSize)is1PPush = false;
		else is1PPush = false;

		return is1PPush;
	}

	void HitBodyProcess(double velo1, double velo2, double pos1, double pos2)
	{

	}

};
