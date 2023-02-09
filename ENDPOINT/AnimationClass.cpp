#include "stdafx.h"
#include "AnimationClass.h"



void AnimationClass::Load(Texture _texture, CSV animationData, int statenumber)
{
	texture = _texture;//画像
	motionTime = Parse<double>(animationData[statenumber][5]) * 1000;//アニメーションの総時間(ミリ秒)
	totalPatterns = Parse<int>(animationData[statenumber][6]);//総パターン数
	endPattern = Parse<int>(animationData[statenumber][8]);//切り取り位置(終)

	startPattern = 0;//切り取り位置(始)
	cutPos.x = startPattern;//画像パターンを初期化
	cutPos.w = texture.width() / totalPatterns;//画像一枚当たりの幅を算出
	cutPos.h = texture.height();//画像一枚当たりの高さを算出
}

void AnimationClass::EffectLoud(Texture _texture, CSV effectData, int lineNumber)
{
	texture = _texture;//画像
	motionTime = Parse<double>(effectData[lineNumber][1]) * 1000;//アニメーションの総時間(ミリ秒)
	totalPatterns = Parse<int>(effectData[lineNumber][2]);//総パターン数

	startPattern = 0;//切り取り位置(始)
	cutPos.x = startPattern;//画像パターンを初期化
	cutPos.w = texture.width() / totalPatterns;//画像一枚当たりの幅を算出
	cutPos.h = texture.height();//画像一枚当たりの高さを算出
}

void AnimationClass::ResetImage()
{
	cutPos.x = startPattern;//画像パターンを初期化
}

void AnimationClass::Draw(Vec2 position,bool _mirror) const
{
	texture(cutPos.x * cutPos.w, cutPos.y * cutPos.h, cutPos.w, cutPos.h).mirrored(_mirror).draw(position);
}

/////////////////////////////////////////////////////////////
//														   //
//														   //
//				　　　　デバック用						   //
//														   //
//														   //
/////////////////////////////////////////////////////////////





