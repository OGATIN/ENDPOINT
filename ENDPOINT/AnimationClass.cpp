#include "stdafx.h"
#include "AnimationClass.h"



void AnimationClass::Reload(Texture _texture, CSV animationData, int statenumber)
{
	texture = _texture;//画像
	motionTime = Parse<double>(animationData[statenumber][5]) * 1000;
	endPattern = Parse<int>(animationData[statenumber][6]);

	startPattern = 0;//
	cutPos.x = startPattern;
	cutPos.w = texture.width() / endPattern;
	cutPos.h = texture.height();//

	//AnimationClass(_texture, animationData, statenumber);
}

void AnimationClass::PatternLoop()
{
	//タイル遷移
	if (currentTime.ms() > OnePatternMotionTime())
	{
		cutPos.x++;
		currentTime.restart();
	}

	//ループ
	if (cutPos.x >= endPattern)
	{
		cutPos.x = startPattern;
		elapsedTime.restart();
	}
}

void AnimationClass::Draw(Vec2 position)const
{
	//描画
	texture(cutPos.x * cutPos.w, cutPos.y * cutPos.h, cutPos.w, cutPos.h).resized(200).draw(position);
}



/////////////////////////////////////////////////////////////
//														   //
//														   //
//				　　　　デバック用						   //
//														   //
//														   //
/////////////////////////////////////////////////////////////

void AnimationClass::DebugDrow()const
{
	font30(U"全体時間 ", motionTime).draw(Scene::Width() - font30(U"全体時間 ", motionTime).region().w, font30.height() * 0);
	font30(U"経過時間 ", elapsedTime.ms()).draw(Scene::Width() - font30(U"経過時間 ", elapsedTime.ms()).region().w, font30.height() * 1);
	font30(U"1枚あたりの時間 ", currentTime.ms()).draw(Scene::Width() - font30(U"1枚あたりの経過時間 ", currentTime.ms()).region().w, font30.height() * 2);
	font30(U"切り取り位置 ", cutPos).draw(Scene::Width() - font30(U"切り取り位置 ", cutPos).region().w, font30.height() * 3);
}



