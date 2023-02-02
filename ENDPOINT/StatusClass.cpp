#include "stdafx.h"
#include "StatusClass.h"

void StatusClass::Reload(CSV statusData, CSV skillPointStatData, CSV experienceBorder, CSV magicSkillPointData, CSV magicOther)
{
	for (int i = 1; i <= level; i++)
	{
		hitPoint = hitPoint + Parse<double>(statusData[1][i]);
		stamina = stamina + Parse<double>(statusData[2][i]);
		mental = mental + Parse<double>(statusData[3][i]);
		power = power + Parse<double>(statusData[4][i]);
		protection = protection + Parse<double>(statusData[5][i]);
		weight = weight + Parse<double>(statusData[6][i]);
		magicPoint = magicPoint + Parse<double>(statusData[8][i]);
		magicPower = magicPower + Parse<double>(statusData[9][i]);

	}

	for (int i = 1; i <= hitPointAllotted; i++)
	{
		hitPoint = hitPoint + Parse<double>(skillPointStatData[1][i]);
	}

	for (int i = 1; i <= staminaAllotted; i++)
	{
		stamina = stamina + Parse<double>(skillPointStatData[2][i]);
	}

	for (int i = 1; i <= mentalAllotted; i++)
	{
		mental = mental + Parse<double>(skillPointStatData[3][i]);
	}

	for (int i = 1; i <= powerAllotted; i++)
	{
		power = power + Parse<double>(skillPointStatData[4][i]);
	}

	for (int i = 1; i <= protectionAllotted; i++)
	{
		protection = protection + Parse<double>(skillPointStatData[5][i]);
	}

	for (int i = 1; i <= weightAllotted; i++)
	{
		weight = weight + Parse<double>(skillPointStatData[6][i]);
	}

	for (int i = 1; i <= magicPointAllotted; i++)
	{
		magicPoint = magicPoint + Parse<double>(skillPointStatData[8][i]);
	}

	for (int i = 1; i <= magicPowerAllotted; i++)
	{
		magicPower = magicPower + Parse<double>(skillPointStatData[9][i]);
	}

	totalValue = magicSkillPoint;

	for (int i = 0; i < 4; i++)
	{
		totalValue += magicSkillPointAllocation[i];
	}

	//魔法が解放されているなら
	if (magicType != MagicType::NONE)
	{
		for (int i = 0; i < 4; i++)
		{
			
			for (int j = 0; j <= magicSkillPointAllocation[i]; j++)
			{
				switch (i)
				{
				case 0:
					magicProficiencyPower += Parse<double>(magicSkillPointData[(int)magicType * 5 + i + 1][j + 2]);
					break;

				case 1:
					subSkill +=  Parse<double>(magicSkillPointData[((int)magicType * 5) + i + 1][j + 2]);
					break;

				case 2:
					coolTime +=  Parse<double>(magicSkillPointData[((int)magicType * 5) + i + 1][j + 2]);
					break;

				case 3:

					if (magicType == MagicType::FIREBALL || magicType == MagicType::THUNDER || magicType == MagicType::HEAL)
					{
						specialFunctioVernValue +=  Parse<double>(magicSkillPointData[((int)magicType * 5) + i + 1][j + 2]);
					}
					else if (magicType == MagicType::TIME || magicType == MagicType::STATUSUP)
					{
						if (j >= 5)
						{
							specialFunctionVerRelease = true;
						}
					}
					break;
				}

			}
		}
	}


	//現在値の更新(仮)
	currentHitPoint = hitPoint;
	currentStamina = stamina;
	currentMental = mental;
	currentMagicPoint = magicPoint;

	//CSVのコピー
	copyStatusData = statusData;
	copySkillPointStatData = skillPointStatData;
	copyExperienceBorder = experienceBorder;
	copyMagicSkillPointData = magicSkillPointData;
	copyMagicOther = magicOther;
};

void StatusClass::GetExperience(int getValue)
{
	if (level < Maxlevel)
	{
		experience += getValue;
	}

	//最大レベルより下で経験値がボーダーを越したとき
	if ((level < Maxlevel) && (experience >= Parse<int>(copyExperienceBorder[level + 3][1])))
	{
		experience = 0;
		level++;
		skillPoint++;

		hitPoint = hitPoint + Parse<double>(copyStatusData[1][level]);
		stamina = stamina + Parse<double>(copyStatusData[2][level]);
		mental = mental + Parse<double>(copyStatusData[3][level]);
		power = power + Parse<double>(copyStatusData[4][level]);
		protection = protection + Parse<double>(copyStatusData[5][level]);
		weight = weight + Parse<double>(copyStatusData[6][level]);
		magicPoint = magicPoint + Parse<double>(copyStatusData[8][level]);
		magicPower = magicPower + Parse<double>(copyStatusData[9][level]);

	}
}

void StatusClass::SkillPointAdd(StatusType statusType, MagicType magicType)
{
	if (statusType != StatusType::MAGICTYPE)
	{
		skillPoint--;
	}

	switch (statusType)
	{
	case StatusType::HP:
		hitPointAllotted++;
		hitPoint = hitPoint + Parse<double>(copySkillPointStatData[1][hitPointAllotted]);
		break;
	case StatusType::STAMINA:
		staminaAllotted++;
		stamina = stamina + Parse<double>(copySkillPointStatData[2][staminaAllotted]);
		break;
	case StatusType::MENTAL:
		mentalAllotted++;
		mental = mental + Parse<double>(copySkillPointStatData[3][mentalAllotted]);
		break;
	case StatusType::POWER:
		powerAllotted++;
		power = power + Parse<double>(copySkillPointStatData[4][powerAllotted]);
		break;
	case StatusType::PROTECTION:
		protectionAllotted++;
		protection = protection + Parse<double>(copySkillPointStatData[5][protectionAllotted]);
		break;
	case StatusType::WEIGHT:
		weightAllotted++;
		weight = weight + Parse<double>(copySkillPointStatData[6][weightAllotted]);
		break;
	case StatusType::MAGICTYPE:
		skillPoint -= SkillPointForMagic;
		ChangeMagic(magicType);
		break;
	case StatusType::MP:
		magicPointAllotted++;
		magicPoint = magicPoint + Parse<double>(copySkillPointStatData[8][magicPointAllotted]);
		break;
	case StatusType::MAGICPOWER:
		magicPowerAllotted++;
		magicPower = magicPower + Parse<double>(copySkillPointStatData[9][magicPowerAllotted]);
		break;
	default:
		break;
	}
}

void StatusClass::ChangeMagic(MagicType _magicType)
{
	magicType = _magicType;
	switch (magicType)
	{
	case MagicType::NONE:
		magicTypeMame = { U"---" };
		break;
	case MagicType::FIREBALL:
		magicTypeMame = { U"火球" };
		break;
	case MagicType::THUNDER:
		magicTypeMame = { U"サンダー" };
		break;
	case MagicType::STATUSUP:
		magicTypeMame = { U"ステータスアップ" };
		break;
	case MagicType::HEAL:
		magicTypeMame = { U"ヒール" };
		break;
	case MagicType::TIME:
		magicTypeMame = { U"タイム" };
		break;
	default:
		break;
	}
}

void StatusClass::GetMagicProficiency(int getValue)
{
	 totalValue = magicSkillPoint;

	for (int i = 0; i < 4; i++)
	{
		totalValue  += magicSkillPointAllocation[i];
	}

	//熟練度を取得(最大値なら取得しない)
	if (totalValue < MaxGetMagicSkillPoint)
	{
		magicProficiency += getValue;

		//ボーダーを超えたら魔法スキルポイントを取得
		if (magicProficiency >= Parse<double>(copyMagicOther[12][totalValue + 1]))
		{
			magicSkillPoint++;
			magicProficiency = 0;

			totalValue = magicSkillPoint;

			for (int i = 0; i < 4; i++)
			{
				totalValue += magicSkillPointAllocation[i];
			}
		}
	}




}

void StatusClass::MagicSkillPointAdd(int changeNumber)
{
	if (changeNumber >= 3 && (magicType == MagicType::TIME || magicType == MagicType::STATUSUP))
	{

		magicSkillPoint -= SpecialFeaturesMagic;

		magicSkillPointAllocation[changeNumber] += SpecialFeaturesMagic;

	}
	else
	{
		magicSkillPoint--;

		magicSkillPointAllocation[changeNumber] ++;
		
	}

	switch (changeNumber)
	{
	case 0:
		magicProficiencyPower += Parse<double>(copyMagicSkillPointData[((int)magicType * 5) + changeNumber + 1][magicSkillPointAllocation[changeNumber] + 2]);
		break;

	case 1:
		subSkill += Parse<double>(copyMagicSkillPointData[((int)magicType * 5) + changeNumber + 1][magicSkillPointAllocation[changeNumber] + 2]);
		break;

	case 2:
		coolTime += Parse<double>(copyMagicSkillPointData[((int)magicType * 5) + changeNumber + 1][magicSkillPointAllocation[changeNumber] + 2]);
		break;

	case 3:

		if (magicType == MagicType::FIREBALL || magicType == MagicType::THUNDER || magicType == MagicType::HEAL)
		{
			specialFunctioVernValue += Parse<double>(copyMagicSkillPointData[((int)magicType * 5) + changeNumber + 1][magicSkillPointAllocation[changeNumber] + 2]);
		}
		else if (magicType == MagicType::TIME || magicType == MagicType::STATUSUP)
		{
			if (magicSkillPointAllocation[changeNumber] >= 5)
			{
				specialFunctionVerRelease = true;
			}
		}
		break;
	}

		


}

/*デバック用*/

void StatusClass::BaseStatusDrow(bool SkillPointRelated)const
{
	String statusName[11][2] =
	{
		{{U"レベル "},	{U" スキルポイント残数 "}},		
		{{U"経験値 "},	{}},
		{{U"HP "},		{U" 振"}},
		{{U"スタミナ"},	{U" 振"}},
		{{U"精神力 "},	{U" 振 "}},
		{{U"攻撃力 "},	{U" 振 "}},
		{{U"守備力 "},	{U" 振 "}},
		{{U"重量 "},	{U" 振 "}},
		{{U"魔法 "},	{}},
		{{U"MP "},		{U" 振 "}},
		{{U"魔力 "},	{U" 振 "}},

	};

	double statusValue[11][2] =
	{
		{{level},		{skillPoint}},
		{{experience},	{}},
		{{hitPoint},	{hitPointAllotted}},
		{{stamina},		{staminaAllotted}},
		{{mental},		{mentalAllotted}},
		{{power},		{powerAllotted}},
		{{protection},	{protectionAllotted}},
		{{weight},		{weightAllotted}},
		{{},			{}},
		{{magicPoint},	{magicPointAllotted}},
		{{magicPower},	{magicPowerAllotted}}
	};	


	for (int i = 0; i < 11; i++)
	{
		if (i != 8)
		{
			font30(statusName[i][0], statusValue[i][0]).draw(0, font30.height() * i);
		}
		else
		{
			font30(statusName[i][0],magicTypeMame).draw(0, font30.height() * i);
		}

		if (SkillPointRelated == true && i != 1 && i != 8)
		{
			font30(statusName[i][1], statusValue[i][1]).draw(font30(statusName[i][0], statusValue[i][0]).region().w, font30.height() * i);
		}
	}
}

void StatusClass::MagicProficiencyRelationDrow() const
{
	String magicRelatedName[7][2] =
	{
		{{U"総取得量　"},{}},
		{{U"魔法熟練度　"},{}},
		{{U"魔法スキルポイント "},{}},
		{{U"威力 "},{U"降"}},
		{{U"サブスキル　"},{U"降"}},
		{{U"クールタイム "},{U"降"}} ,
		{{U"特殊枠 "},{U"降"} },
	};

	double magicRelatedValue[7][2] =
	{
		{{totalValue},{}},
		{{magicProficiency},{}},
		{{magicSkillPoint},{}},
		{{magicProficiencyPower},{magicSkillPointAllocation[0]}},
		{{subSkill},{magicSkillPointAllocation[1]}},
		{{coolTime} ,{magicSkillPointAllocation[2]}},
		{{specialFunctioVernValue} ,{magicSkillPointAllocation[3]}},

	};

	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			if (j == 0 || i > 2)
			{
				font30(magicRelatedName[i][j], magicRelatedValue[i][j]).draw(font30.spaceWidth() * 30 * j, font30.height() * i);
			}
		}
	}
	font30(a).draw(0, 600);

}
