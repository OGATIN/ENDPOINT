#include "stdafx.h"
#include "EffectClass.h"

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
	creationPos = changePos - (effectBase.cutPos.size / 2);
}


bool EffectClass::IsDelete()
{
	if (effectBase.totalPatterns < effectBase.cutPos.x)
	{
		return true;
	}
}
