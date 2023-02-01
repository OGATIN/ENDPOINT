#pragma once
#include"Base.h"
#include"PlayerClass.h"
#include"EnemyClass.h"


class Stage1 : public App::Scene
{
private:
	const int MapSize = 16;
	const Vec2 MapChipSize = { 32,32 };

	
    Texture BackScreen      { U"Material/3.MAP/6.町 背景.png" };
    Texture UnderGround     { U"Material/3.MAP/使うやつ.png" };

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

	Audio WalkAudio			{ U"Material/4.SE/1.歩き.mp3" , Loop::Yes };
	Audio RunAudio			{ U"Material/4.SE/2.走り.mp3" , Loop::Yes };
	Audio JumpAudio			{ U"Material/4.SE/3.ジャンプ.mp3" };
	Audio FistAudio			{ U"Material/4.SE/4.拳.mp3" };
	Audio SwordAudio		{ U"Material/4.SE/5.剣.mp3" };
	Audio HammerAudio		{ U"Material/4.SE/6.鈍器.mp3" };
	Audio FireBallAudio		{ U"Material/4.SE/7.火球.mp3" };
	Audio ThunderAudio		{ U"Material/4.SE/8.サンダー.mp3" };
	Audio HealAudio			{ U"Material/4.SE/9.回復.mp3" };
	Audio StatusUpAudio		{ U"Material/4.SE/10.ステータスアップ.mp3" };
	Audio TimeAudio			{ U"Material/4.SE/11.タイム.mp3" };
	Audio DamageAudio		{ U"Material/4.SE/12.ダメージ.mp3" };
	Audio GuardAudio		{ U"Material/4.SE/13.防御した時.mp3" };
	Audio GuardDamageAudio	{ U"Material/4.SE/14.防御中攻撃を受けた時.mp3" };
	Audio GuardBreakAudio	{ U"Material/4.SE/15.防御割れ.mp3" };
	Audio Pause1Audio		{ U"Material/4.SE/16.ゲームを一時停止した時1.mp3" };
	Audio Pause2Audio		{ U"Material/4.SE/17.ゲームを一時停止した時.mp3" };
	Audio DropAudio			{ U"Material/4.SE/18.ドロップアイテムを落とした時.mp3" };
	Audio PickUpAudio		{ U"Material/4.SE/19.ドロップアイテムを拾った時.mp3" };

	
	CSV AnimationData{ U"ConfigData/アニメーションデータ.csv" };
	CSV BasicStatusData{ U"ConfigData/基礎ステータスデータ.csv" };
	CSV SkillPointStatusData{ U"ConfigData/スキルポイントステータスデータ.csv" };
	CSV ExperienceBorder{ U"ConfigData/経験値ボーダー.csv" };

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

	Audio SEAudio[19] =
	{
		WalkAudio,
		RunAudio,
		JumpAudio,
		FistAudio,
		SwordAudio,
		HammerAudio,
		FireBallAudio,
		ThunderAudio,
		HealAudio,
		StatusUpAudio,
		TimeAudio,
		DamageAudio,
		GuardAudio,
		GuardDamageAudio,
		GuardBreakAudio,
		Pause1Audio,
		Pause2Audio,
		DropAudio,
		PickUpAudio
	};


	PlayerClass Player = { playerPNG ,SEAudio,AnimationData ,BasicStatusData ,SkillPointStatusData,ExperienceBorder };

	EnemyClass Enemey = { enemeyPNG ,SEAudio,AnimationData ,BasicStatusData, SkillPointStatusData ,ExperienceBorder };

	CSV mapData{ U"ConfigData/map.csv" };

	Vec2 cameraPos = {0,0};

	// プレイヤーインデックス (0 - 3)
	size_t playerIndex = 0;
	const Array<String> options = Range(1, 4).map([](int32 i) {return U"{}P"_fmt(i); });

	// デッドゾーンを有効にするか
	bool enableDeadZone = true;

	// 振動 (0.0 - 1.0)
	XInputVibration vibration;


	//デバック用
	Font font{ 30 };

	//経験値関連使い方講座
	int S = 0;
	StatusType tentative = StatusType::HP;
	String statusTypeName = U"HP";;	//状態
	int Missing;
	String isMissing = U"";		//足りてないか
	String isMax = U"";			//
	

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

	/// @brief 壁との当たり判定
	void MapHitGround(GameObject &_gameobject);

	void Camera(int screenDivisionNumber, int leftRange, int rightRange);

	/// @brief 体同士が衝突した際の当たり判定で使う移動量を計算
	/// @param velox1 一キャラ目の移動値X
	/// @param velox2 二キャラ目の移動値X
	/// @return 結果の移動値
	double HitBodyVelocity(double velox1, double velox2);

	/// @brief 二つの移動地のうち、どちらが押しているかを判定
	/// @param velox1 1P
	/// @param velox2 2P
	/// @return 1Pが押しているならtrue,それ以外ならfalse,同値でもfalse
	bool Is1PPush(double velox1, double velox2);
	
};
