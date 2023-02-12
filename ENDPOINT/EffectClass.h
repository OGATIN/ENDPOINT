#pragma once
#include"AnimationClass.h"

class EffectClass
{
public:
	AnimationClass effectBase;

	Vec2 creationPos;

	Vec2 vector = {0,0};

	RectF hitBox;

	Stopwatch currentTime;

	EffectType effectType;

	bool isMirror = false;

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

	void HitBoxUpdate();

	void Animation(double _motionEndMagnification = 1);

	void FireBallAnimation();

	void CreationPosChange(Vec2 changePos);

	void EffectTypeChange(EffectType changeType, double changeSpeed = 0);

	void MirrorChange(bool changeMirror);

	void Draw()const;

};

