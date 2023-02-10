#pragma once
#include"AnimationClass.h"

class EffectClass
{
public:
	AnimationClass effectBase;

	Vec2 creationPos;
	RectF hitBox;

	Stopwatch currentTime;

	

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

	void CreationPosChange(Vec2 changePos);

	void HitBoxUpdate();

};

