#pragma once
#include"EffectClass.h"


enum class SEstate
{
	WAIKSE, RUNSE, JUMPSE, DAMAGESE,FISTSE,  SWORDSE, FIREBALLSE
};

class GameObject
{
public:
	AnimationClass animation[4][8];//武器の種類×4 各モーションの種類×9

	Audio audio[19];

	Stopwatch currentTime;//時間

	StatusClass status;//ステータス

	StateType state = StateType::WAIT;//現在の状態

	Rect shiftInternalHitRect[4][13][11];  //補正

	Vec2 screenPosition = { 0,0 };//画面の左上を中心とした座標
	Vec2 MapPosition = { 0,0 };//MAPの左上を中心とした座標
	Vec2 velocity = { 0,0 };//ベクトル
	Rect hitBox = { 0,0,0,0 };//当たり判定

	Vec2 fistFiringPoint = { 205,130 };
	Vec2 fistFiringMirrorPoint = { 115,130 };

	double gravity = 0.5;//重力量
	bool isLanding = false;//着地しているか
	bool isMirror = false;//反転
	bool isDescendStand = false;//下入力されているか(台用)
	bool isRearGap = false;

	/*const */double charaSpeedMax = 10;
	double charaSpeed = 0;
	double speedAdd = 0;
	double frictionForce = 1;//摩擦力
	double additionalAmount = 2;//加算量

	/*const */double jumpPowerMax = 20;
	double jumpPower = 0;
	int jumpTiming = 6;

	EffectClass Effects[3];
	Array<EffectClass>effects;

	//デバック用フォント
	Font font30{ 30 };

	String statename;
	String weaponname;

	//時間(タイム作る時にデバックから昇格するかも)

	double motionEndMagnification = 1;//モーション終了時間倍率


	GameObject() {};

	GameObject(Texture _animation[4][20], EffectClass effect[3], Audio _audio[19], CSV AnimationData, CSV TextureShiftData, CSV statusData, CSV skillPointStatData, CSV experienceBorder, CSV magicSkillPointData, CSV magicOther)
	{
		Reload(_animation, effect,_audio, AnimationData, TextureShiftData, statusData, skillPointStatData, experienceBorder, magicSkillPointData, magicOther);
	};

	//機能

	/// @brief 再読み込み
	void Reload(Texture _animation[4][20], EffectClass effect[3], Audio _audio[19], CSV AnimationData, CSV TextureShiftData, CSV statusData, CSV skillPointStatData, CSV experienceBorder, CSV magicSkillPointData, CSV magicOther);

	/// @brief 毎フレーム更新する情報
	void Update();

	/// @brief モーションを始める
	void MotionStart();

	/// @brief モーションを一時停止する、一時停止中なら再開する
	void MotionStop();

	//モーションを動かす
	void PatternLoop();

	//一つのモーションを動かす
	void OnePattern();

	void EffectAdd(EffectType effectType, Vec2 addpos);

	void EffectUpdate();

	/// @brief 状態に応じた処理を行う
	void StateManagement();

	/// @brief 待機の処理
	void WaitProcess();

	/// @brief 歩きの処理
	void WalkProcess();

	/// @brief 走りの処理
	void RunProcess();

	/// @brief ジャンプの処理
	void JumpProcess();

	/// @brief 対空の処理
	void FallingProcess();

	/// @brief 受けの処理
	void ReceiveProcess();

	/// @brief 攻撃の処理
	void AttackProcess();

	void FistProcess();

	void SwordProcess();

	void MagicProcess();

	/// @brief 待機状態への遷移
	void ChangeWait();

	/// @brief 歩き状態への遷移(右)
	void ChangeWalkR();

	/// @brief 歩き状態への遷移(左)
	void ChangeWalkL();

	/// @brief 走り状態への遷移(右)
	void ChangeRunR();

	/// @brief 走り状態への遷移(左)
	void ChangeRunL();

	/// @brief ジャンプ状態への遷移
	void ChangeJump();

	/// @brief 空中状態への遷移
	void ChangeFalling();

	/// @brief 
	void ChangeReceive(Vec2 knockBack);

	/// @brief 
	void ChangeAttack();

	/// @brief 
	void ChangeAttackMagic();

	/// @brief animationのテクスチャを描画する
	void Draw()const;

	void EffectDraw(bool hitBoxDraw = false)const;

	/// @brief 再生を停止する
	void AudioStop();

	/*デバック用*/

	/// @brief 現在の 状態 武器 を表示します。
	void StatusDraw()const;

	/// @brief 時間関連のデバック
	void TimeDebuggDraw()const;

	/// @brief 座標のデバック表示
	void CoordinateRelated()const;

	void EffectsDraw()const;

	void HitBoxDraw(ColorF drawColor = Palette::White)const;

	/*内部データ用*/

	//一つのモーションが終わったかどうか
	bool isOneLoop();

	Vec2 ObjectCenterWorldPoint()const noexcept;

	Rect GetHitRect()const;

	/// @brief 上
	/// @return 
	int GetTop();

	/// @brief 下
	/// @return 
	int GetBottom();

	/// @brief 左
	/// @return 
	int GetLeft();

	/// @brief 右
	/// @return 
	int GetRight();


	/*マップの当たり判定*/

	/// @brief 上面の当たり判定の点を作成できます。
	/// @param mapchip_px MAPのピクセル数
	/// @param division 当たり判定の分割数
	/// @param number 分割数から何番目か
	/// @return MAPの配列番号
	Point MapTopSidePoint(Point mapchip_px, int division, int number);

	/// @brief 下面の当たり判定の点を作成できます。
	/// @param mapchip_px MAPのピクセル数
	/// @param division 当たり判定の分割数
	/// @param number 分割数から何番目か
	/// @return MAPの配列番号
	Point MapBottomSidePoint(Point mapchip_px, int division, int number);

	/// @brief 左側の当たり判定の点を作成できます。
	/// @param mapchip_px MAPのピクセル数
	/// @param division 当たり判定の分割数
	/// @param number 分割数から何番目か
	/// @return MAPの配列番号
	Point MapLeftSidePoint(Point mapchip_px, int division, int number);

	/// @brief 右側の当たり判定の点を作成できます。
	/// @param mapchip_px MAPのピクセル数
	/// @param division 当たり判定の分割数
	/// @param number 分割数から何番目か
	/// @return MAPの配列番号
	Point MapRightSidePoint(Point mapchip_px, int division, int number);
};

