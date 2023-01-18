#pragma once
class GameObject
{
public:
	CSV AnimationData{ U"ConfigData/アニメーションデータ.csv" };
	Texture waitingMotionPNG{ U"Material/1.img/1.待機モーション.png" };
	Texture waikMotionPNG{ U"Material/1.img/1.待機モーション.png" };

	AnimationClass waitMotion{ waitingMotionPNG, AnimationData,1 };

	void AnimationDraw(AnimationClass animation,Vec2 position)const;

	void AnimationHitBox(AnimationClass animation,CSV hitBoxData);

	void AnimationProcess(AnimationClass animation);


	StateType state = StateType::WAIT;

	StatusClass status;//ステータス

	Vec2 position = { 0,0 };
	Vec2 velocity = { 0,0 };
	Rect hitBox = { 0,0,0,0 };

	double gravity = 0.5;
	bool isJump = false;

	int jumpPower = 10;
	int charaSpeed = 5;

	
	//PlayerClass(Texture _wait, CSV statusData)
	/*{
		playerStatus.Reload(statusData);
		playerAnimation.Reload(_wait);
	};*/

	Rect GetHitRect(AnimationClass animation);
	int GetTop(AnimationClass animation);
	int GetBottom(AnimationClass animation);
	int GetLeft(AnimationClass animation);
	int GetRight(AnimationClass animation);

	void StateManagement();
	void StateManagementDraw()const;
	void MotionStart();
	void MotionStop();
	void Jump();
	void Move();

	void Initialize();
	void PlayerUpdate();
	void PlayerDraw()const;
};

