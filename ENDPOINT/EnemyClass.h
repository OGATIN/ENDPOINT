#pragma once

class EnemyClass
{
public:
	GameObject gameObject;

	Vec2 localCameraPos{0,0};

	//Circle sR{gameObject.GetHitRect().topCenter(),300};
	//Circle aR{gameObject.GetHitRect().topCenter(),100};
	Circle sR{ gameObject.GetHitRect().pos,300 };
	Circle aR{ gameObject.GetHitRect().pos,100 };

	EnemyClass(Texture _animation[4][20], EffectClass effect[2], Audio _audio[19], CSV AnimationData, CSV TextureShiftData, CSV statusData, CSV skillPointStatData, CSV experienceBorder, CSV magicSkillPointData, CSV magicOther)
	{
		gameObject.Reload(_animation, effect, _audio, AnimationData, TextureShiftData, statusData, skillPointStatData, experienceBorder, magicSkillPointData, magicOther);
	};

	/// @brief 座標関連を更新します。
	/// @param camerapos カメラ座標
	void Update(Vec2 camerapos);

	/// @brief AIの切り替え処理を行います。AIのパターンとUpdateを内蔵させます。
	/// @param camerapos カメラ座標
	/// @param Player プレイヤーオブジェクト(比較用)
	void AIManegement(Vec2 camerapos,GameObject Player);

	/// @brief テストAI(バグの元なので一旦使わないで)
	/// @param camerapos カメラ座標
	/// @param pos 指定位置
	void TestAI(Vec2 camerapos,Vec2 pos);

	/// @brief 拳AI(マネージャーに入れてないので一旦Updateを内蔵させてます。)
	/// @param Player  プレイヤーオブジェクト(比較用)
	/// @param camerapos カメラ座標(Update消すときに一緒に消して)
	void Fist(GameObject Player, Vec2 camerapos); //拳

	/// @brief 描画
	void Draw()const;


	/*デバック表示*/

	/// @brief デバック表示(当たり判定など)
	void DebugDraw()const;
};

