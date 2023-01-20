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

void AnimationClass::Draw(Vec2 position) const
{
	texture(cutPos.x * cutPos.w, cutPos.y * cutPos.h, cutPos.w, cutPos.h).resized(200).draw(position);
}



/////////////////////////////////////////////////////////////
//														   //
//														   //
//				　　　　デバック用						   //
//														   //
//														   //
/////////////////////////////////////////////////////////////





