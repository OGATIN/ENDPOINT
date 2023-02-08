#include "SetUp.h"
#undef System


void SetUp::Initialize()
{
	//最初の情報定義
	mainVolumeGauge.Set(mainVolumeGaugeRect, GameData::selectMainVolume, U"マスター");
	BGMVolumeGauge.Set(BGMVolumeGaugeRect, GameData::selectBGMVolume, U"BGM");
	SEVolumeGauge.Set(SEVolumeGaugeRect, GameData::selectSEVolume, U"SE");

	//音量定義
	mainVolumeGauge.AudioSet(selectAudio, GameData::MainVolume);
	BGMVolumeGauge.AudioSet(selectAudio, GameData::MainVolume * GameData::BGMVolume);
	SEVolumeGauge.AudioSet(selectAudio, GameData::MainVolume * GameData::SEVolume);

	isEnable = true;
	isFirst = false;

	firstMenuChar = { U"音量",U"キー設定",U"セーブ",U"ロード",U"説明",U"終わる" };
	firstMenu.StringSet(firstMenuChar, { 10,10 });

}

void SetUp::SetUpEnable()
{
	//最初のループでは読まない,ESCAPEが押されたら設定画面を閉じて初期化フラグを立てる
	if (KeyEscape.down() && not isFirst)
	{
		isEnable = false;
		isFirst = true;
	}

	if (isEnable)
	{
		if (isFirst)
		{
			Initialize();
		}
		update();
		draw();
	}
}

void SetUp::update()
{
	///todoList:
	// ●ゲージのキー対応23/1/16
	// ●フォントの書体を変える,UIデザイン煮詰める23/1/16
	// キャラのサイズ感確認
	// 選択音に音量調整のボリュームが適応されてない
	// タイトルから飛んだ時違うやつ表示、二重で表示されないようにするべし
	// マウスの消去
	// menuIDの初期化
	// 長押しした時の処理
	// マップとの当たり判定
	// 重力の実装
	// animationclass作成
	// CSVファイル読み込み
	// 移動の後隙

	//positionがanimationclass
	//playerの当たり判定の情報をposition差分のRect作成,CSV

	ConfigGauge* gauges[] = { &mainVolumeGauge ,&BGMVolumeGauge,&SEVolumeGauge };
	
	//シーン管理
	switch (selectScene)
	{
	case SetUp::NowScene::MenuSelect:

		firstMenu.Update();

		switch (firstMenu.IsCurrent())
		{
		case 0:
			if (KeyZ.down() || KeyEnter.down() || firstMenu.IsMouseOver() && MouseL.down())
			{
				selectScene = NowScene::AudioConfig;
				selectAudio.playOneShot(GameData::MainVolume * GameData::SEVolume);
			}
			break;
		case 1:
			if (KeyZ.down() || KeyEnter.down() || firstMenu.IsMouseOver() && MouseL.down())
			{
				selectScene = NowScene::KeyConfig;
				selectAudio.playOneShot(GameData::MainVolume * GameData::SEVolume);
			}
			break;
		case 2:
			if (KeyZ.down() || KeyEnter.down() || firstMenu.IsMouseOver() && MouseL.down())
			{
				selectScene = NowScene::Save;
				selectAudio.playOneShot(GameData::MainVolume * GameData::SEVolume);
			}
			break;
		case 3:
			if (KeyZ.down() || KeyEnter.down() || firstMenu.IsMouseOver() && MouseL.down())
			{
				selectScene = NowScene::Load;
				selectAudio.playOneShot(GameData::MainVolume * GameData::SEVolume);
			}
			break;
		case 4:
			if (KeyZ.down() || KeyEnter.down() || firstMenu.IsMouseOver() && MouseL.down())
			{
				selectScene = NowScene::Explanation;
				selectAudio.playOneShot(GameData::MainVolume * GameData::SEVolume);
			}
			break;
		case 5:
			if (KeyZ.down() || KeyEnter.down() || firstMenu.IsMouseOver() && MouseL.down())
			{
				selectAudio.playOneShot(GameData::MainVolume * GameData::SEVolume);
				System::Exit();
			}
			break;
		}
		break;
	case SetUp::NowScene::AudioConfig:
		//戻る
		if (SimpleGUI::ButtonAt(U"戻る", Vec2(Scene::Width() - 70, Scene::Height() - 30)))
		{
			selectAudio.playOneShot(GameData::MainVolume * GameData::SEVolume);
			selectScene = NowScene::MenuSelect;
		}

		
		if (KeyS.down() || KeyDown.down())
		{
			gaugeID += 1;

			if (gaugeID > 2)
			{
				gaugeID = 0;
			}
		}

		if (KeyW.down() || KeyUp.down())
		{
			gaugeID -= 1;

			if (gaugeID < 0)
			{
				gaugeID = 2;
			}
		}

		for (auto& gauge : gauges)
		{
			gauge->CreateGauge();

			gauge->isSelect = false;
		}

		gauges[gaugeID]->isSelect = true;



		for (int i = 0; i < 3; i++)
		{

			if (gauges[i]->gaugeRect.mouseOver())
			{
				gaugeID = i;
			}
		}

		GameData::selectMainVolume = mainVolumeGauge.selectVolume;
		GameData::selectSEVolume = BGMVolumeGauge.selectVolume;
		GameData::selectBGMVolume = SEVolumeGauge.selectVolume;
		break;
	case SetUp::NowScene::KeyConfig:
		//戻る
		if (SimpleGUI::ButtonAt(U"戻る", Vec2(Scene::Width() - 70, Scene::Height() - 30)))
		{
			selectAudio.playOneShot(GameData::MainVolume * GameData::SEVolume);
			selectScene = NowScene::MenuSelect;
		}
		break;
	case SetUp::NowScene::Save:
		//戻る
		if (SimpleGUI::ButtonAt(U"戻る", Vec2(Scene::Width() - 70, Scene::Height() - 30)))
		{
			selectAudio.playOneShot(GameData::MainVolume * GameData::SEVolume);
			selectScene = NowScene::MenuSelect;
		}
		break;
	case SetUp::NowScene::Load:
		//戻る
		if (SimpleGUI::ButtonAt(U"戻る", Vec2(Scene::Width() - 70, Scene::Height() - 30)))
		{
			selectAudio.playOneShot(GameData::MainVolume * GameData::SEVolume);
			selectScene = NowScene::MenuSelect;
		}
		break;
	case SetUp::NowScene::Explanation:
		//戻る
		if (SimpleGUI::ButtonAt(U"戻る", Vec2(Scene::Width() - 70, Scene::Height() - 30)))
		{
			selectAudio.playOneShot(GameData::MainVolume * GameData::SEVolume);
			selectScene = NowScene::MenuSelect;
		}
		break;
	default:
		break;
	}
}


void SetUp::draw()
{
	//※要検証
	//Scene::SetBackground(Color(85, 85, 85,1));//シーンの色を半透明な灰色に設定
	Rect BackGround{ 0,0,Scene::Width(),Scene::Height() }; 
	BackGround.draw(ColorF(0.3,0.7));

	bool dmy;

	switch (selectScene)
	{
	case SetUp::NowScene::MenuSelect:

		//メニュー描画
		firstMenu.InRectDraw(true);

		break;
	case SetUp::NowScene::AudioConfig:

		gaugeBackRect.draw().drawFrame(2,Palette::Black);
		//ゲージ描画,デバッグモードなら当たり判定も描画
		mainVolumeGauge.GaugeDraw();
		BGMVolumeGauge.GaugeDraw();
		SEVolumeGauge.GaugeDraw();

		dmy = (SimpleGUI::ButtonAt(U"戻る", Vec2(Scene::Width() - 70, Scene::Height() - 30)));

		//font30(SetUpMenuName[0]).draw(10,10,Palette::White);
		break;
	case SetUp::NowScene::KeyConfig:
		dmy = (SimpleGUI::ButtonAt(U"戻る", Vec2(Scene::Width() - 70, Scene::Height() - 30)));
		break;
	case SetUp::NowScene::Save:
		dmy = (SimpleGUI::ButtonAt(U"戻る", Vec2(Scene::Width() - 70, Scene::Height() - 30)));
		break;
	case SetUp::NowScene::Load:
		dmy = (SimpleGUI::ButtonAt(U"戻る", Vec2(Scene::Width() - 70, Scene::Height() - 30)));
		break;
	case SetUp::NowScene::Explanation:
		dmy = (SimpleGUI::ButtonAt(U"戻る", Vec2(Scene::Width() - 70, Scene::Height() - 30)));
		break;
	default:
		break;
	}

	
}
