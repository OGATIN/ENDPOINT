#pragma once

class EnemyClass
{
public:
	GameObject gameObject;


	EnemyClass(Texture _animation[4][20], Audio _audio[19], CSV AnimationData, CSV statusData, CSV skillPointStatData, CSV experienceBorder, CSV magicSkillPointData, CSV magicOther)
	{
		gameObject.Reload(_animation, _audio, AnimationData, statusData, skillPointStatData, experienceBorder, magicSkillPointData, magicOther);
	};

	void TestAI(Vec2 pos);

	void AIManegement();

	void Draw()const;
	void DebugDraw()const;
};

