#include "stdafx.h"
#include "AnimationClass.h"


/*内部データ*/


double AnimationClass::OnePatternMotionTime()
{
	return motionTime / endPattern;
}


//void AnimationClass::PatternSet()
//{
//	startPattern = 0;//
//	endPattern = animationPattern;
//	cutPos.x = startPattern;
//}
//
//void AnimationClass::TextureWidthHeightSet()
//{
//	cutPos.w = texture.width() / animationPattern;
//	cutPos.h = texture.height() / 1;//
//}

