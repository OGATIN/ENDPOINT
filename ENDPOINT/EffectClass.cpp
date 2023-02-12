#include "stdafx.h"
#include "EffectClass.h"

void EffectClass::Update()
{
	if (effectType == EffectType::FISTEFFECT)
	{
		Animation();

	}
	else if (effectType == EffectType::FIREBALLEFFECT)
	{
		LongDistanceAnimation();
	}


	HitBoxUpdate();
}

void EffectClass::Animation(double _motionEndMagnification)
{
	if (currentTime.isRunning() == false)
	{
		currentTime.start();
	}

	if (effectBase.totalPatterns > effectBase.cutPos.x)
	{
		//タイル遷移
		if (currentTime.ms() > (effectBase.OnePatternMotionTime() * _motionEndMagnification))
		{
			effectBase.cutPos.x++;
			currentTime.restart();
		}
	}

	//デバック用
	effectBase.elapsedTime = ElapsedTime();

}

void EffectClass::LongDistanceAnimation()
{
	if (currentTime.isRunning() == false)
	{
		currentTime.start();
	}


	//タイル遷移
	if ((switchingTime * conut) < currentTime.ms())
	{
		conut++;

		if (effectBase.cutPos.x < effectBase.totalPatterns - 1)
		{
			effectBase.cutPos.x++;
		}
		else
		{
			effectBase.ResetImage();

		}

	}
}



void EffectClass::CreationPosChange(Vec2 changePos)
{
	creationPos = changePos - (effectBase.cutPos.size / 2 * effectBase.size);
}

void EffectClass::EffectTypeChange(EffectType changeType)
{
	effectType = changeType;
}

void EffectClass::HitBoxUpdate()
{
	hitBox = RectF(creationPos, (effectBase.texture.width() / effectBase.totalPatterns * effectBase.size), effectBase.texture.height() * effectBase.size);
}

double EffectClass::ElapsedTime()
{
	return ((effectBase.OnePatternMotionTime() * effectBase.cutPos.x) + currentTime.ms());
}



