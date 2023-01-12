#include"Scene.h"

void Main()
{
	//映像出力設定
	Window::Resize(DisplayResolution::HD_1280x720);//ウィンドウサイズ設定
	Scene::SetBackground(ColorF(0.3, 0.3, 0.3));//シーンの色を灰色に設定
	

	//シーン管理
	SceneManager<SceneName, GameData> manager;

	manager.add<SetUp>(SceneName::SetUp);
	manager.add<Stage1>(SceneName::Stage1);
	manager.add<Stage2>(SceneName::Stage2);
	manager.add<Stage3>(SceneName::Stage3);
	manager.add<Stage4>(SceneName::Stage4);
	manager.add<Title>(SceneName::Title);
	manager.add<GameOver>(SceneName::GameOver);
	manager.add<GameClear>(SceneName::GameClear);
	manager.add<Credit>(SceneName::Credit);
	manager.add<Finish>(SceneName::Finish);




	while (System::Update())
	{
		if (!manager.update())
		{
			break;
		}
	}
}
