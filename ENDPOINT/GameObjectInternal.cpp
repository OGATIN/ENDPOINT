#include "stdafx.h"
#include "GameObject.h"

Rect GameObject::GetHitRect()
{
	return Rect{ (int)position.x + shiftInternalHitRect[0][0].x
				,(int)position.y + shiftInternalHitRect[0][0].y
				,shiftInternalHitRect[0][0].w,shiftInternalHitRect[0][0].h};
}

int GameObject::GetTop()
{
	return (int)position.y + shiftInternalHitRect[0][0].y;
}

int GameObject::GetBottom()
{
	return (int)position.y + shiftInternalHitRect[0][0].y + shiftInternalHitRect[0][0].h;
}

int GameObject::GetLeft()
{
	return (int)position.x + shiftInternalHitRect[0][0].x;
}

int GameObject::GetRight()
{
	return (int)position.x + shiftInternalHitRect[0][0].x + shiftInternalHitRect[0][0].w;
}


//左下
Point GameObject::MapRightBottom(Vec2 camerapos, Point mapchip_px)
{

	return (Point{
	(position.asPoint().x + camerapos.asPoint().x + shiftInternalHitRect[0][0].pos.x) / mapchip_px.x,
	 (position.asPoint().y + camerapos.asPoint().y + shiftInternalHitRect[0][0].pos.y + shiftInternalHitRect[0][0].h) / mapchip_px.y
	});

}

//右下
Point GameObject::MapLeftBottom(Vec2 camerapos, Point mapchip_px)
{
	return (Point{
	(position.asPoint().x + camerapos.asPoint().x + shiftInternalHitRect[0][0].pos.x + shiftInternalHitRect[0][0].w) / mapchip_px.x,
	 (position.asPoint().y + camerapos.asPoint().y + shiftInternalHitRect[0][0].pos.y + shiftInternalHitRect[0][0].h) / mapchip_px.y
	});
}

<<<<<<< HEAD


/*
Rect GameObject::MapsPositionRect(Vec2 camerapos,Vec2 mapchip_px)
{
	Rect mappos;

	mappos.x =  (GetHitRect().x + camerapos.x) / mapchip_px.x;
	mappos.y =  (GetHitRect().y + camerapos.y) / mapchip_px.y;
	mappos.w = shiftInternalHitRect[0][0].w / mapchip_px.x;
	mappos.h = shiftInternalHitRect[0][0].h / mapchip_px.y;


	return Rect();
}
*/

=======
>>>>>>> ogatin
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
//void GameObject::PlayerDraw() const
//{
//	//画像描画
//	StateManagementDraw();
//
//	//デバック用
//	status.DaseStatusDrow();//ステータスの表示
//	//animation.TimeDrow();//時間の表示
//}
