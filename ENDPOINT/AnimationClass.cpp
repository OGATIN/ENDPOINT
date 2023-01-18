#include "stdafx.h"
#include "AnimationClass.h"

double AnimationClass::OnePatternMotionTime()
{
	return motionTime / animationPattern;
}

void AnimationClass::TextureWidthHeightSet()
{
	widthSize  = texture.width() / animationPattern;
	heightSize = texture.height() / 1;
}

void AnimationClass::PatternSet()
{
	startPattern = 0;
	endPattern = animationPattern;
	currentPattern = startPattern;
}

void AnimationClass::PatternLoop()
{
	//タイル遷移
	if (currentTime.ms() > OnePatternMotionTime())
	{
		currentPattern += 1;
		currentTime.restart();
	}

	//ループ
	if (currentPattern > endPattern)
	{
		currentPattern = startPattern;
	}
}

void AnimationClass::Initialize()
{
	TextureWidthHeightSet();

	PatternSet();

	currentTime.start();
}

void AnimationClass::Reload(Texture wait)
{
	waiting = wait;
}

void AnimationClass::TimeDrow()const
{
	font30(currentTime.ms()).draw(Scene::Width() - font30(currentTime.ms()).region().w, 0);
}

void AnimationClass::Wait()
{
	//1枚目
	if ((1000 / 2) >= currentTime.ms())
	{
		cutPos.y = 0;
	}
	else if ((1000/2) <= currentTime.ms() && 1000 >= currentTime.ms())//2枚目
	{
		cutPos.y = 1;
	}
	else //終了処理
	{
		currentTime.restart();
	}
}

void AnimationClass::WaitDraw(Vec2 position)const
{
	//描画
	waiting(cutPos.x * cutPos.w, cutPos.y * cutPos.h, cutPos.w, cutPos.h).resized(200).draw(position);
}


