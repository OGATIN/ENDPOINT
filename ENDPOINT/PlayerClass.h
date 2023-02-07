#include"GameObject.h"
#include"Menu.h"

#pragma once

class PlayerClass
{
public:
	PlayerClass() {};
	PlayerClass(Texture _animation[4][20], Audio _audio[19], CSV AnimationData, CSV TextureShiftData, CSV statusData, CSV skillPointStatData, CSV experienceBorder, CSV magicSkillPointData, CSV magicOther)
	{
		gameObject.Reload(_animation, _audio, AnimationData,TextureShiftData,statusData,skillPointStatData,experienceBorder,magicSkillPointData,magicOther);
	};

	enum class MenuTransition
	{
		FirstScene, Item, Status, SkillPoint
	};

	MenuTransition selectMenu = MenuTransition::FirstScene;

	GameObject gameObject;

	//バーの定義
	Bar hitpointBar{};
	Bar magicpointBar{ Palette::Blue};
	Bar mentalpointBar{ Palette::Purple};
	Bar staminapointBar{ Palette::Yellow};

	Array<String> firstMenuChara = { U"アイテム",U"ステータス",U"スキルポイント",U"閉じる" };
	Menu firstMenu{ firstMenuChara ,{20,20} };

	Array<String> itemMenuChara = {  };
	Menu itemMenu{ itemMenuChara ,{100,10} };

	Array<String> statusMenuChara = { U"レベル",U"HP",U"MP",U"スタミナ",U"精神力",U"攻撃力",U"魔力",U"防御力",U"重量", U"魔法"};
	Array<String> magicMenuChara = {U"威力",U"速度",U"クールタイム",U"大きさ" };
	Menu statusMenu{ statusMenuChara, { 350,20 } };
	Menu magicMenu{ magicMenuChara, { 380,((statusMenuChara.size()) * 45) + 15}};

	Array<String> skillPointMenuChara = { U"通常",U"魔法",U"戻る" };
	Menu skillPointMenu{ skillPointMenuChara ,{340,20} };

	Array<double> statusChar;
	Array<double> magicChar;
	
	Font font30{ 30 ,U"Material/6.font/jfdotfont-20150527/JF-Dot-ShinonomeMin12.ttf" };//フォント

	bool isOnline = false;

	StatusClass status;

	Audio selectAudio{ U"Material/4.SE/16.ゲームを一時停止した時1.mp3" };

	void ConfigOnlineProcess();

	void ConfigOnlineDraw()const;

	void Initialize();

	void Update();

	void StatusDraw()const;

	void Draw()const;

	void DebugDraw()const;
};




