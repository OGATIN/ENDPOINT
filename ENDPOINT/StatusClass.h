#pragma once

enum class StatusType
{
	HP, STAMINA, MENTAL, POWER, PROTECTION, WEIGHT, MAGICTYPE, MP, MAGICPOWER,
};

enum class MagicType
{
	FIREBALL , THUNDER , HEAL, STATUSUP , TIME,NONE,
};

enum class WeaponType
{
	FIST, SWORD, HAMMER, CANE
};

class StatusClass
{
public:

	
	int level = 1;//プレイヤーのレベル

	int skillPoint = 6;//残ってるスキルポイントの値(デフォルト1)

	int hitPointAllotted = 0;//割り振られた値(HP)
	int staminaAllotted = 0;//割り振られた値(スタミナ)
	int mentalAllotted = 0;//割り振られた値(精神力)
	int powerAllotted = 0;//割り振られた値(攻撃力)
	int protectionAllotted = 0;//割り振られた値(防御力)
	int weightAllotted = 0;//割り振られた値(重量)
	int magicPointAllotted = 0;//割り振られた値(MP)
	int magicPowerAllotted = 0;//割り振られた値(魔力)

	int experience = 0;//現在の経験値


	int magicProficiency = 0;//現在の魔法熟練度
	
	int magicSkillPoint = 0;//魔法スキルポイント
	int magicSkillPointAllocation[4] = { 0,0,0,0 };//魔法スキルポイントを割り振った値


	/*ここから上をいじると下の数値が変化します。*/

	double hitPoint = 0;		//HP
	double stamina = 0;			//スタミナ
	double mental = 0;			//精神力
	double power = 0;			//攻撃力
	double protection = 0;		//防御力
	double weight = 0;			//重量
	MagicType magicType = MagicType::NONE;//魔法の種類
	double magicPoint = 0;		//MP
	double magicPower = 0;		//魔力

	//現在値
	double currentHitPoint = 0;  //HP
	double currentStamina = 0;	  //スタミナ
	double currentMental = 0;	  //精神力
	double currentMagicPoint = 0; //MP


	//魔法によって値の意味が変わります。
	double magicProficiencyPower = 0;//威力 ※magicSkillPointの0
	double subSkill = 4;//魔法によって変わります。※magicSkillPointの1
	double coolTime = 0;//クールタイム ※magicSkillPointの2
	double specialFunctioVernValue = 0.2;//魔法によって変わります (火球、サンダー、ヒールの時に使用) ※magicSkillPointの3
	bool specialFunctionVerRelease = false;//魔法によって変わります(ステータスアップとタイムの時に使用)※magicSkillPointの3


	WeaponType weapon = WeaponType::SWORD;//現在の武器

	//レベルアップ時の処理用
	int preLevel = 1;

	//魔法熟練度

	int totalValue = 0; //魔法スキルポイントの総取得量

	//比較用
	const int Maxlevel = 30;//プレイヤーの最大レベル
	const int MaxSkillPoint = 10;//スキルの最大まで割り振れる値
	const int SkillPointForMagic = 5;//魔法を取得するのに必要なスキルポイント量
	const int MaxGetMagicSkillPoint = 10;//魔法スキルポイントを取得できる最大値
	const int MaxMagicSkillPoint = 5;//魔法スキルポイントの最大まで割り振れる値
	const int SpecialFeaturesMagic = 5;//特殊な機能を魔法に付与させるときの消費量


	//エクセルデータのコピー保存場所

	CSV copyStatusData;//ステータスデータ
	CSV copySkillPointStatData;//スキルポイントステータスデータ
	CSV copyExperienceBorder;//経験値ボーダー
	CSV copyMagicSkillPointData;//魔法スキルポイントデータ
	CSV copyMagicOther;//魔法その他

	//魔法名表示用
	String magicTypeMame = { U"---" };

	//デバック用フォント
	Font font30{ 30 };

	int a = 0;

	StatusClass() {};

	StatusClass(CSV statusData, CSV skillPointStatData,CSV experienceBorder,CSV magicSkillPointData, CSV magicOther)
	{
		Reload(statusData,skillPointStatData,experienceBorder,magicSkillPointData,magicOther);
	};


	/// @brief 再読み込み
	/// @param statusData 基礎ステータスデータ.csv
	/// @param skillPointStatData スキルポイントステータスデータ.csv
	/// @param experienceBorder 経験値ボーダー.csv
	/// @param magicSkillPointData 
	/// @param magicOther 
	void Reload(CSV statusData, CSV skillPointStatData, CSV experienceBorder, CSV magicSkillPointData, CSV magicOther);

	/// @brief 経験値を取得し、ボーダーを超えるならレベルアップします。(レベルが最大値なら取得しません)
	/// @param getValue 取得量
	void GetExperience(int getValue);

	/// @brief 次にレベルアップするまでの値
	/// @return 次にレベルアップするまでの値
	int NextLevel()const;

	/// @brief スキルポイント割り振りを行えます。(下記のIsEnoughSkillPoints()とIsAllocateSkillPoints()で変更していいかを調べてから変更してください)
	/// @param statusType 割り振りたいステータスの種類
	/// @param magicType もし魔法を変更したいなら変更したい魔法の種類を入力
	void SkillPointAdd(StatusType statusType, MagicType magicType = MagicType::NONE);

	/// @brief 魔法を変更します。(SkillPointAdd()に内蔵されてるので教会用かデバック用)
	/// @param _magicType 変更したい魔法を
	void ChangeMagic(MagicType _magicType);

	/// @brief　熟練度を取得し、ボーダーを超えるなら魔法スキルポイントを取得します。(スキルポイントが最大なら取得しない)
	/// @param getValue 基本は1ずつしか上がらないのでデバック用
	void GetMagicProficiency(int getValue = 1);


	/// @brief 魔法スキルポイントを振り分けます。
	/// @param changeNumber 振り分けたい行番号
	void MagicSkillPointAdd(int changeNumber);


	/*デバック用*/

	/// @brief ステータスの表示
	/// @param SkillPointRelated  trueならスキルポイント関連も表示します。 
	void BaseStatusDrow(bool SkillPointRelated = false)const;

	/// @brief 魔法熟練度関連の表示
	void MagicProficiencyRelationDrow()const;


	/*内部データ用*/

	/// @brief スキルポイントを割り振る際スキルポイントが足りているかを調べてくれます。
	/// @param statusType 割り振りたいステータスの種類
	/// @return 0なら足りています。それ以上ならいくら足りていないかを返してくれます。
	int IsEnoughSkillPoint(StatusType statusType)const;

	/// @brief スキルポイントポイントが最大値じゃないかを調べてくれます。※魔法の場合は既に魔法が選択されているか(これがないと最悪エラーで起動すらできなくなります)
	/// @param statusType 割り振りたいステータスの種類
	/// @return MAXでないならtrue MAXならflase
	bool IsAllocateSkillPoint(StatusType statusType);

	/// @brief 魔法スキルポイントを割り振る際スキルポイントが足りているかを調べてくれます。
	/// @param changeNumber 振り分けたい行番号
	/// @return 0なら足りています。それ以上ならいくら足りていないかを返してくれます。
	int IsEnoughMagicSkillPoint(int changeNumber);

	/// @brief 魔法スキルポイントポイントが最大値じゃないかを調べてくれます。(これがないと最悪エラーで起動すらできなくなります)
	/// @param changeNumber 振り分けたい行番号
	/// @return MAXでないならtrue MAXならflase
	bool IsAllocateMagicSkillPoint(int changeNumber);

	/// @brief レベルが上がったかの判定
	/// @return レベルが上がったときにtrue
	bool IsLevelUp();



};


