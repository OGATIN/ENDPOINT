#pragma once
class GameObject
{
public:
	CSV AnimationData{ U"ConfigData/アニメーションデータ.csv" };
	Texture waitingMotionPNG{ U"Material/1.img/1.待機モーション.png" };
	Texture waikMotionPNG{ U"Material/1.img/1.待機モーション.png" };

	AnimationClass waitMotion{ waitingMotionPNG, AnimationData,1 };

	void AnimationDraw(AnimationClass animation,Vec2 position);

	void AnimationHitBox(AnimationClass animation,CSV hitBoxData);

	void AnimationProcess(AnimationClass animation);
};

