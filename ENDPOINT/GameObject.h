#pragma once
class GameObject
{
public:

	AnimationClass waitMotion;

	StatusClass status;//ステータス

	StateType state = StateType::WAIT;


	Rect waitPosDifference = { 62,30,35,130 };

	Vec2 position = { 0,0 };
	Vec2 velocity = { 0,0 };
	Rect hitBox = { 0,0,0,0 };

	double gravity = 0.5;
	bool isJump = false;

	int jumpPower = 10;
	int charaSpeed = 5;


	GameObject(Texture _wait,CSV AnimationData, CSV statusData)
	{
		waitMotion.Reload(_wait, AnimationData,1);/*@*/
		status.Reload(statusData);
	};

	//機能

	void PlayerUpdate();

	void MotionStart();

	void MotionStop();

	void Jump();

	void Move();

	void StateManagement();

	void StateManagementDraw()const;

	//デバック用

	void Initialize();




	//ここから下はGameObjectInternal.cppに

	/*内部データ用*/


	//使ってないの
    //CSV AnimationData{ U"ConfigData/アニメーションデータ.csv" };
    //Texture waitingMotionPNG{ U"Material/1.img/1.待機モーション.png" };
    //Texture waikMotionPNG{ U"Material/1.img/1.待機モーション.png" };
    //void AnimationProcess(AnimationClass animation);
    //void AnimationDraw(AnimationClass animation,Vec2 position)const;
    //void AnimationHitBox(AnimationClass animation,CSV hitBoxData);
	//Rect GetHitRect(AnimationClass animation);
	//int GetTop(AnimationClass animation);
	//int GetBottom(AnimationClass animation);
	//int GetLeft(AnimationClass animation);
	//int GetRight(AnimationClass animation);
	//void PlayerDraw()const;これいる？

};

