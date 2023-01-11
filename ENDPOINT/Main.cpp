#include"Scene.h"

void Main()
{
	//�f���o�͐ݒ�
	Window::Resize(DisplayResolution::HD_1280x720);//�E�B���h�E�T�C�Y�ݒ�
	Scene::SetBackground(ColorF(0.3, 0.3, 0.3));//�V�[���̐F���D�F�ɐݒ�
	

	//�V�[���Ǘ�
	SceneManager<SceneName, GameData> manager;

	manager.add<Stage1>(SceneName::Stage1);
	manager.add<Stage2>(SceneName::Stage2);
	manager.add<Stage3>(SceneName::Stage3);
	manager.add<Stage4>(SceneName::Stage4);
	manager.add<Title>(SceneName::Title);
	manager.add<GameOver>(SceneName::GameOver);
	manager.add<GameClear>(SceneName::GameClear);
	manager.add<Credit>(SceneName::Credit);
	manager.add<SetUp>(SceneName::SetUp);
	manager.add<Finish>(SceneName::Finish);




	while (System::Update())
	{
		if (!manager.update())
		{
			break;
		}
	}
}