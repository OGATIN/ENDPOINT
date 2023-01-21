#pragma once
class GameObject
{
public:



	//CSV AnimationData{ U"ConfigData/アニメーションデータ.csv" };

	//AnimationClass waitMotion;
	//AnimationClass walkMotion;
	//AnimationClass runMotion;
	//AnimationClass jumpMotion;
	//AnimationClass receiveMotion;
	//AnimationClass attackMotion;
	//AnimationClass magicMotion;
	//AnimationClass guardMotion;
	//AnimationClass notstaminaMotion;

	AnimationClass animation[4][9];//武器の種類×4 各モーションの種類×9

	Stopwatch currentTime;		//時間

	StatusClass status;//ステータス

	StateType state = StateType::WAIT;//現在の状態

	WeaponType weapon = WeaponType::FIST;//現在の武器

	int stateTypeNumber = 0;//現在の状態番号
	int weaponTypeNumber = 0;//現在の武器番号

	Stopwatch animationTime;

	Rect shiftInternalHitRect[1][1] = { { {62,30,35,130} } };  //補正

	Vec2 position = { 0,0 };
	Vec2 velocity = { 0,0 };
	Rect hitBox = { 0,0,0,0 };

	double gravity = 0.5;
	bool isJump = false;
	bool isMotionLock = false;
	bool isHit = false;
	bool isMirror = false;

	int jumpPower = 10;
	int charaSpeed = 5;


	//デバック用フォント
	Font font30{ 30 };

	String statename;
	String weaponname;
	
	GameObject(Texture _animation,Texture _walkTex,Texture _runTex,Texture _jumpTex,CSV AnimationData, CSV statusData)
	{
		animation[0][0].Reload(_animation, AnimationData,1);/*@*/
		animation[0][1].Reload(_walkTex, AnimationData,2);/*@*/
		animation[0][2].Reload(_runTex, AnimationData,3);/*@*/
		animation[0][3].Reload(_jumpTex, AnimationData,4);/*@*/
		status.Reload(statusData);
	};

	//機能

	/// @brief 毎フレーム更新する情報
	void Update();

	void MotionStart();

	void MotionStop();

	//モーションを動かす
	void PatternLoop();

	/// @brief ジャンプの処理
	void Jump();

	/// @brief 歩きの処理
	void Walk();

	/// @brief 走りの処理
	void Run();

	/// @brief 移動の処理
	void Move();

	/// @brief 状態に応じた処理を行う
	void StateManagement();

	/// @brief animationのテクスチャを描画する
	void Draw()const;

	/// @brief 状態を変化させる処理
	void ChangeState();



	//デバック用
	void Initialize();

	/// @brief 現在の 状態 武器 を表示します。
	void StatusDraw()const;

	/// @brief 時間関連のデバック
	void TimeDebuggDraw()const;


	
	/*内部データ用*/
	Rect GetHitRect();
	int GetTop();
	int GetBottom();
	int GetLeft();
	int GetRight();


	Point MapLeftBottom(Vec2 camerapos, Point mapchip_px);
	Point MapRightBottom(Vec2 camerapos, Point mapchip_px);


	//使ってないの
    //CSV AnimationData{ U"ConfigData/アニメーションデータ.csv" };
    //Texture waitingMotionPNG{ U"Material/1.img/1.待機モーション.png" };
    //Texture waikMotionPNG{ U"Material/1.img/1.待機モーション.png" };
    //void AnimationProcess(AnimationClass animation);
    //void AnimationDraw(AnimationClass animation,Vec2 position)const;
    //void AnimationHitBox(AnimationClass animation,CSV hitBoxData);
	//void PlayerDraw()const;これいる？

};

