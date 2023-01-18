#include "stdafx.h"
#include "GameObject.h"

void GameObject::AnimationProcess(AnimationClass animation)
{
	animation.PatternLoop();
}

void GameObject::AnimationDraw(AnimationClass animation,Vec2 position)const
{
	animation.texture(animation.currentPattern * animation.widthSize, 0, animation.widthSize, animation.heightSize).draw(position);
}

void GameObject::AnimationHitBox(AnimationClass animation, CSV hitBoxData)
{

}

Rect GameObject::GetHitRect(AnimationClass animation)
{
	return Rect{ (int)position.x + animation.waitPosDifference.x
				,(int)position.y + animation.waitPosDifference.y
				,animation.waitPosDifference.w,animation.waitPosDifference.h };
}

int GameObject::GetTop(AnimationClass animation)
{
	return (int)position.y + animation.waitPosDifference.y;
}

int GameObject::GetBottom(AnimationClass animation)
{
	return (int)position.y + animation.waitPosDifference.y + animation.waitPosDifference.h;
}

int GameObject::GetLeft(AnimationClass animation)
{
	return (int)position.x + animation.waitPosDifference.x;
}

int GameObject::GetRight(AnimationClass animation)
{
	return (int)position.x + animation.waitPosDifference.x + animation.waitPosDifference.w;
}




void GameObject::StateManagement()
{
	switch (state)
	{
	case StateType::WAIT:
		AnimationProcess(waitMotion);
		break;
	case StateType::WAIK:
		break;
	case StateType::RUN:
		break;
	case StateType::JUMP:
		break;
	case StateType::RECEIVE:
		break;
	case StateType::ATTACK:
		break;
	case StateType::MAGIC:
		break;
	case StateType::GUARD:
		break;
	case StateType::NOTSTAMINA:
		break;
	default:
		break;
	}
}

void GameObject::StateManagementDraw() const
{
	switch (state)
	{
	case StateType::WAIT:
		AnimationDraw(waitMotion, position);
		break;
	case StateType::WAIK:
		break;
	case StateType::RUN:
		break;
	case StateType::JUMP:
		break;
	case StateType::RECEIVE:
		break;
	case StateType::ATTACK:
		break;
	case StateType::MAGIC:
		break;
	case StateType::GUARD:
		break;
	case StateType::NOTSTAMINA:
		break;
	default:
		break;
	}
}


void GameObject::MotionStop()
{
	////ストップウォッチが停止しているか
	//if (playerAnimation.currentTime.isRunning())
	//{
	//	//計測中なら停止(経過時間はそのまま)
	//	playerAnimation.currentTime.pause();
	//}
	//else
	//{
	//	//停止中なら計測
	//	playerAnimation.currentTime.resume();
	//}
}

void GameObject::Jump()
{
	//↑が押されたらジャンプ
	if (KeyUp.down())
	{
		velocity.y = -jumpPower;
	}
}

void GameObject::Move()
{
	//左右移動(仮)
	if (KeyRight.pressed() || KeyD.down())
	{
		position.x += charaSpeed;
	}
	if (KeyLeft.pressed() || KeyA.down())
	{
		position.x -= charaSpeed;
	}
}

void GameObject::Initialize()
{
	//初期座標
	position = { 400,425 };

	//初期移動量
	velocity = { 0,0 };

	Initialize();

	//ストップウォッチスタート
	//MotionStart();
}

void GameObject::PlayerUpdate()
{
	//当たり判定更新
	//hitBox = GetHitRect();

	//座標更新
	position += velocity;

	//重力加算
	velocity.y += gravity;

	//状態管理
	StateManagement();

	Jump();

	Move();

	//デバック用
	status.DaseStatusUpdate();//ステータスの表示

	if (KeySpace.down())
	{
		//一時停止
		MotionStop();
	}
}

void GameObject::PlayerDraw() const
{
	//画像描画
	StateManagementDraw();

	//デバック用
	status.DaseStatusDrow();//ステータスの表示
	//animation.TimeDrow();//時間の表示
}



