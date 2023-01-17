#include"Scene.h"
#undef System

void Main()
{
	//映像出力設定
	Window::Resize(DisplayResolution::HD_1280x720);//ウィンドウサイズ設定
	Window::SetStyle(WindowStyle::Sizable);//ウィンドウを手動でリサイズできるようにする
	Scene::SetBackground(ColorF(0.3, 0.3, 0.3));//シーンの色を灰色に設定
	System::SetTerminationTriggers(UserAction::CloseButtonClicked);// エスケープキーを押しても終了しないようになる
	SetUp setUp;

	//シーン管理
	SceneManager<SceneName, GameData> manager;

	manager.add<Title>(SceneName::Title);
	manager.add<Town>(SceneName::Town);
	manager.add<Stage1>(SceneName::Stage1);
	manager.add<Stage2>(SceneName::Stage2);
	manager.add<Stage3>(SceneName::Stage3);
	manager.add<Stage4>(SceneName::Stage4);
	manager.add<GameOver>(SceneName::GameOver);
	manager.add<GameClear>(SceneName::GameClear);
	manager.add<Credit>(SceneName::Credit);
	manager.add<Finish>(SceneName::Finish);




	while (System60::Update())
	{
		// ウィンドウタイトルに直近のフレームレートを表示
		Window::SetTitle(Profiler::FPS());

		if (!manager.update())
		{
			break;
		}

		if (KeyEscape.down())
		{
			setUp.isEnable = true;
		}
		setUp.SetUpEnable();
	}

	
}
