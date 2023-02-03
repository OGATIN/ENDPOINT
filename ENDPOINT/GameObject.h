#pragma once
class GameObject
{
public:
	AnimationClass animation[4][9];//武器の種類×4 各モーションの種類×9

	Audio audio[19];

	Stopwatch currentTime;//時間

	StatusClass status;//ステータス

	StateType state = StateType::FALLING;//現在の状態

	WeaponType weapon = WeaponType::FIST;//現在の武器

	//int stateTypeNumber = 0;//現在の状態番号
	//int weaponTypeNumber = 0;//現在の武器番号

	Stopwatch animationTime;

	Rect shiftInternalHitRect[1][1][1];  //補正

	Vec2 position = { 0,0 };
	Vec2 velocity = { 0,0 };
	Rect hitBox = { 0,0,0,0 };

	double gravity = 0.5;
	bool isLanding = false;
	bool isMirror = false;

	const int charaSpeedMax = 10;
	const int jumpPowerMax = 20;
	int jumpPower = 0;
	int charaSpeed = 0;


	//デバック用フォント
	Font font30{ 30 };

	String statename;
	String weaponname;

	RectF textureSize = {0,0,0,0};
	int clickCount = 0;
	Circle firstPoint = {0,0,1};
	RectF secondRect = {0,0,0,0};

	//時間(タイム作る時にデバックから昇格するかも)
	bool speedChange = false;
	double motionEndMagnification = 1;//ここが増えるとモーションの終了に時間がかかる

	bool frameNumber = false;

	GameObject() {};

	GameObject(Texture _animation[4][20], Audio _audio[19], CSV AnimationData, CSV statusData, CSV skillPointStatData, CSV experienceBorder, CSV magicSkillPointData, CSV magicOther)
	{

		for (int j = 0; j < 4; j++)
		{
			for (int i = 0; i < 6; i++)
			{
				//とりあえず共通のデータはここでロード
				animation[j][i].Reload(_animation[j][i], AnimationData, i + 1);

			}

			//animation[j][7].Reload(_animation[j][7], AnimationData, 8);//
			//animation[j][7].Reload(_animation[j][7], AnimationData, 9);
		}

		for (int i = 0; i < 19; i++)
		{
			audio[i] = _audio[i];
		}

		status.Reload(statusData, skillPointStatData,experienceBorder, magicSkillPointData, magicOther);
	};

	//機能

	void Reload(Texture _animation[4][20], Audio _audio[19], CSV AnimationData, CSV statusData, CSV skillPointStatData, CSV experienceBorder, CSV magicSkillPointData, CSV magicOther);

	/// @brief 毎フレーム更新する情報
	void Update();

	void MotionStart();

	void MotionStop();

	//モーションを動かす
	void PatternLoop();

	//一つのモーションを動かす
	void OnePattern();

	//一つのモーションを動かす
	bool isOneLoop();

	/// @brief 待機の処理
	void WaitProcess();

	/// @brief 歩きの処理
	void WalkProcess();

	/// @brief 走りの処理
	void RunProcess();

	/// @brief ジャンプの処理
	void JumpProcess();

	/// @brief ジャンプの処理
	void FallingProcess();

	/// @brief ジャンプの処理
	void LandingProcess();

	/// @brief ジャンプの処理
	void ReceiveProcess();

	/// @brief ジャンプの処理
	void AttackProcess();

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

	/// @brief ジャンプ状態への遷移
	void ChangeFalling();

	/// @brief ジャンプ状態への遷移
	void ChangeReceive();

	/// @brief ジャンプ状態への遷移
	void ChangeAttack();

	/// @brief 状態に応じた処理を行う
	void StateManagement();

	/// @brief animationのテクスチャを描画する
	void Draw()const;

	/// @brief 再生を停止する
	void AudioStop();

	//デバック用
	void Initialize();

	/// @brief 現在の 状態 武器 を表示します。
	void StatusDraw()const;

	/// @brief 時間関連のデバック
	void TimeDebuggDraw()const;

	void playerCollsioninputoutdeg();
	void playerCollsioninputoutdegDraw()const;

	void MotionEndMagnificationIncrease();
	void MotionEndMagnificationDecrease();

	void MotionFrameSkip();
	void MotionFrameBack();


	
	/*内部データ用*/
	Rect GetHitRect()const;
	int GetTop();
	int GetBottom();
	int GetLeft();
	int GetRight();

	/*マップの当たり判定*/
	Point MapLeftBottom(Vec2 camerapos, Point mapchip_px);
	Point MapRightBottom(Vec2 camerapos, Point mapchip_px);
	Point MapLeftTop(Vec2 camerapos, Point mapchip_px);
	Point MapRightTop(Vec2 camerapos, Point mapchip_px);




	//使ってないの
    //CSV AnimationData{ U"ConfigData/アニメーションデータ.csv" };
    //Texture waitingMotionPNG{ U"Material/1.img/1.待機モーション.png" };
    //Texture WALKMotionPNG{ U"Material/1.img/1.待機モーション.png" };
    //void AnimationProcess(AnimationClass animation);
    //void AnimationDraw(AnimationClass animation,Vec2 position)const;
    //void AnimationHitBox(AnimationClass animation,CSV hitBoxData);
	//void PlayerDraw()const;これいる？

};

