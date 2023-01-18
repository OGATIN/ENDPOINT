#include "stdafx.h"
#include "GameObject.h"

void GameObject::AnimationDraw(AnimationClass animation,Vec2 position)
{
	animation.texture.draw(position);
}

void GameObject::AnimationHitBox(AnimationClass animation, CSV hitBoxData)
{
}

void GameObject::AnimationProcess(AnimationClass animation)
{
}
