#pragma once

class EnemyClass
{
public:
	GameObject gameObject;

	EnemyClass(Texture _animation[4][20], Audio _audio[19], CSV AnimationData, CSV statusData)
	{
		gameObject.Reload(_animation, _audio, AnimationData, statusData);
	};

	void TestAI(Vec2 pos);

	void AIManegement();

	void Draw()const;
	void DebugDraw()const;

};

