#pragma once
#include"AnimationClass.h"

class EffectClass
{
public:
	AnimationClass effectBase;

	Vec2 creationPos;
	RectF hitBox;

	Stopwatch currentTime;

	EffectType effectType;

	double switchingTime = 200;//アニメーションを繰り返したいときの切り替え時間

	int conut = 1;

	EffectClass() {};

	/// @brief エフェクト
	/// @param _texture 画像
	/// @param effectData エフェクトデータ
	/// @param lineNumber 行数
	EffectClass(Texture _texture, CSV effectData, int lineNumber)
	{
		effectBase.EffectLoud(_texture, effectData, lineNumber);
	};

	void Update();

	void Animation(double _motionEndMagnification = 1);

	void LongDistanceAnimation();

	void EffectTypeChange(EffectType changeType);

	void CreationPosChange(Vec2 changePos);

	void HitBoxUpdate();

	/// @brief アニメーションの全体時間(現在)
	/// @return アニメーションの全体時間(現在)
	double ElapsedTime();

};

