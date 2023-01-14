#include "stdafx.h"
#include "AnimationClass.h"

void AnimationClass::Reload(Texture wait)
{
	waiting = wait;
}

void AnimationClass::TimeDrow()
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

	//描画
	waiting(cutPos.x * cutPos.w, cutPos.y * cutPos.h, cutPos.w, cutPos.h).resized(200).draw(pos);
}


