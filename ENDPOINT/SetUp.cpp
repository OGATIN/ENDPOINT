#include "SetUp.h"


SetUp::~SetUp()
{

}

void SetUp::Initialize()
{
	//最初の情報定義
	mainVolumeGauge.Set(mainVolumeGaugeRect, GameData::selectMainVolume, U"マスター");
	BGMVolumeGauge.Set(BGMVolumeGaugeRect, GameData::selectEffectVolume, U"BGM");
	SEVolumeGauge.Set(SEVolumeGaugeRect, GameData::selectBGMVolume, U"SE");

	//音量定義
	mainVolumeGauge.AudioSet(selectAudio, GameData::MainVolume * GameData::EffectVolume);
	BGMVolumeGauge.AudioSet(selectAudio, GameData::MainVolume * GameData::EffectVolume);
	SEVolumeGauge.AudioSet(selectAudio, GameData::MainVolume * GameData::EffectVolume);
}

void SetUp::update()
{
	//シーン管理
	switch (selectScene)
	{
	case SetUp::NowScene::MenuSelect:

		for (int i = 0; i < MenuNumber; i++)
		{
			//当たり判定とマウスが交差していたらフラグを立てる
			if (MenuHitBox[i].mouseOver())
			{
				isSelectMenu[i] = true;
			}
			else
			{
				isSelectMenu[i] = false;
			}

			//シーン遷移
			switch (i)
			{
			case 0:
				if (MenuHitBox[i].mouseOver() && MouseL.down())
				{
					selectScene = NowScene::AudioConfig;
				}
				break;
			case 1:
				if (MenuHitBox[i].mouseOver() && MouseL.down())
				{
					selectScene = NowScene::KeyConfig;
				}
				break;
			case 2:
				if (MenuHitBox[i].mouseOver() && MouseL.down())
				{
					selectScene = NowScene::Save;
				}
				break;
			case 3:
				if (MenuHitBox[i].mouseOver() && MouseL.down())
				{
					selectScene = NowScene::Load;
				}
				break;
			case 4:
				if (MenuHitBox[i].mouseOver() && MouseL.down())
				{
					selectScene = NowScene::Explanation;
				}
				break;
			case 5:
				if (MenuHitBox[i].mouseOver() && MouseL.down())
				{
					changeScene(SceneName::Title);
				}
				break;
			}
		}
		break;
	case SetUp::NowScene::AudioConfig:
		break;
	case SetUp::NowScene::KeyConfig:
		break;
	case SetUp::NowScene::Save:
		break;
	case SetUp::NowScene::Load:
		break;
	case SetUp::NowScene::Explanation:
		break;
	default:
		break;
	}
	
	

}


void SetUp::draw() const
{
	switch (selectScene)
	{
	case SetUp::NowScene::MenuSelect:
		//メニュー描画
		for (int i = 0; i < MenuNumber; i++)
		{
			if (isSelectMenu[i])
			{
				//選択されていれば黄色
				font30(SetUpMenuName[i]).draw(10, 10 + i * 45, Palette::Yellow);
			}
			else
			{
				//選択されていなければ白色
				font30(SetUpMenuName[i]).draw(10, 10 + i * 45, Palette::White);
			}
		}
		break;
	case SetUp::NowScene::AudioConfig:
		//ゲージ描画
		mainVolumeGauge.GaugeDraw();
		BGMVolumeGauge.GaugeDraw();
		SEVolumeGauge.GaugeDraw();
		break;
	case SetUp::NowScene::KeyConfig:
		break;
	case SetUp::NowScene::Save:
		break;
	case SetUp::NowScene::Load:
		break;
	case SetUp::NowScene::Explanation:
		break;
	default:
		break;
	}

	
}
