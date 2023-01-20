#include "stdafx.h"
#include "GameObject.h"


//使ってない
//void GameObject::AnimationProcess(AnimationClass animation)
//{
//	animation.PatternLoop();
//}

//void GameObject::AnimationDraw(AnimationClass animation,Vec2 position)const
//{
//	animation.texture(animation.currentPattern * animation.widthSize, 0, animation.widthSize, animation.heightSize).draw(position);
//}
//
//void GameObject::AnimationHitBox(AnimationClass animation, CSV hitBoxData)
//{
//
//}
//

//Rect GameObject::GetHitRect(AnimationClass animation)
//{
//	return Rect{ (int)position.x + animation.waitPosDifference.x
//				,(int)position.y + animation.waitPosDifference.y
//				,animation.waitPosDifference.w,animation.waitPosDifference.h };
//}
//
//int GameObject::GetTop(AnimationClass animation)
//{
//	return (int)position.y + animation.waitPosDifference.y;
//}
//
//int GameObject::GetBottom(AnimationClass animation)
//{
//	return (int)position.y + animation.waitPosDifference.y + animation.waitPosDifference.h;
//}
//
//int GameObject::GetLeft(AnimationClass animation)
//{
//	return (int)position.x + animation.waitPosDifference.x;
//}
//
//int GameObject::GetRight(AnimationClass animation)
//{
//	return (int)position.x + animation.waitPosDifference.x + animation.waitPosDifference.w;
//}

//void GameObject::PlayerDraw() const
//{
//	//画像描画
//	StateManagementDraw();
//
//	//デバック用
//	status.DaseStatusDrow();//ステータスの表示
//	//animation.TimeDrow();//時間の表示
//}
