#include "stdafx.h"
#include "EffectClass.h"

void EffectClass::Update()
{
	Animation();
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

}

void EffectClass::CreationPosChange(Vec2 changePos)
{
	creationPos = changePos - (effectBase.cutPos.size / 2 * effectBase.size);
}

void EffectClass::HitBoxUpdate()
{
	hitBox = RectF(creationPos, (effectBase.texture.width() / effectBase.totalPatterns * effectBase.size), effectBase.texture.height() * effectBase.size);
}



