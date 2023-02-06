#pragma once

class EnemyClass
{
public:
	GameObject gameObject;

	//Circle sR{gameObject.GetHitRect().topCenter(),300};
	//Circle aR{gameObject.GetHitRect().topCenter(),100};
	Circle sR{gameObject.GetHitRect().pos,300};
	Circle aR{gameObject.GetHitRect().pos,100};

	EnemyClass(Texture _animation[4][20], Audio _audio[19], CSV AnimationData, CSV statusData, CSV skillPointStatData, CSV experienceBorder)
	{
		gameObject.Reload(_animation, _audio, AnimationData, statusData, skillPointStatData, experienceBorder);
	};

	void TestAI(Vec2 pos);

	void AIManegement();


	void Fist(GameObject Player); //拳



	void Draw()const;
	void DebugDraw()const;
};

