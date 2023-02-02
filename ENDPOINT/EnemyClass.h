#pragma once

class EnemyClass
{
public:
	GameObject gameObject;

	EnemyClass(Texture _animation[4][20], Audio _audio[19], CSV AnimationData, CSV statusData, CSV skillPointStatData, CSV experienceBorder)
	{
		gameObject.Reload(_animation, _audio, AnimationData, statusData, skillPointStatData, experienceBorder);
	};

	void TestAI(Vec2 pos);

	void AIManegement();

	void Draw()const;
	void DebugDraw()const;
};

