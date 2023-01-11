/*

このファイルを includeすると

1280*720 つまり家庭用ゲーム機のD4端子に相当した画素数になり、６０フレーム毎秒になる

stdafx.h　に  #include  するだけ

：設定方法-----------------------------------------------------


ソリューションにある stdafx.h　に1行追加する

--------stdafx.h--------------------------------------------
# pragma once
//# define NO_S3D_USING
# include <Siv3D.hpp>
#include"Siv3D0_6_5_1280x720_60fps_20221107.h"	// <<<<<<<<● 1行追加 ● <<<<<<

==================================================================

画面サイズを変更したい場合、★の行を変更する

例１：規定にある画素数（800,600）にしたい場合

このファイル内の★の行を探して変更する
～～
const Size WindowSize = DisplayResolution::SVGA_800x600;// ★サイズ変更したい場合、ここを変更
const Size SceneSize = DisplayResolution::SVGA_800x600;	// ★サイズ変更したい場合、ここを変更
～～

例２：ウィンドウサイズを800x600 シーンサイズを400x300にしたい場合-----------------------------------------------------

const Size WindowSize = DisplayResolution::SVGA_800x600;	// ★サイズ変更したい場合、ここを変更
const Size SceneSize = Size(400,300);						// ★サイズ変更したい場合、ここを変更


*/


#pragma once
# include <Siv3D.hpp> // OpenSiv3D v0.6.4

//#include<chrono>
using namespace std::chrono;

const Size WindowSize = DisplayResolution::HD_1280x720;	// ★サイズ変更したい場合、ここを変更
const Size SceneSize = DisplayResolution::HD_1280x720;	// ★サイズ変更したい場合、ここを変更

class System2
{
	System2() {}
public:
	inline static high_resolution_clock::time_point start; // 計測スタート時刻を保存 //XXXX
	/// @brief 画面の画素数決定
	/// @return 画面サイズを変更して成功したらtrue?(失敗はないと考えられるが)
	inline static bool SetDisplayResolution()
	{
		bool ok = Window::Resize(WindowSize);// ①
		Scene::Resize(SceneSize);//② この順番で行う
		return ok;
	}
	inline static void SetFullScreen(Size size = { 0,0 })
	{
		if (size.x == 0 && size.y == 0)
		{
			size = displayResolution;
		}
		else
			displayResolution = size;
		//Scene::SetResizeMode(ResizeMode::Keep);
		SetDisplayResolution();
		Window::SetFullscreen(true);
	}

	static const int FPS = 60; // 1秒間に1画面を書き換える回数
	/// @brief フルスクリーンの画素数
	inline static Size displayResolution;// = DisplayResolution::HD_1280x720;
#pragma optimize("", off)
	/// @brief 画面表示前の初期化　意味ないコードも含まれている
	/// @return 
	static bool Initialize()
	{
		start = high_resolution_clock::now();      // 計測スタート時刻を保存
		displayResolution = WindowSize;

		auto end = high_resolution_clock::now();
		auto durtion = end - start;        // 要した時間を計算
		// auto msec = duration_cast<std::chrono::nanoseconds>(durtion).count();
		return true;	// ここでは最適化無視しないと怖い
	}
	/// @brief System::Update() を乗っ取り
	/// @return 
	static bool Update()
	{
		static bool displaySet = false;
		if (not displaySet)
		{
			displaySet = true;
			SetDisplayResolution();	// 本当はMain()に入る直前に行いたいのだが仕方なく
		}

		auto elapset = [&]()
		{
			auto end = high_resolution_clock::now();
			auto durtion = end - start;        // 要した時間を計算
			auto msec = duration_cast<std::chrono::nanoseconds>(durtion).count();
			return msec;
		};
		long long sleepTime = elapset() / 1000000 / 2;

#pragma region フレームスキップ
		// フレームスキップ 1フレーム時間を超えていたらフレームスキップさせる
// 動作未確認、不具合があればこの部分を削除予定
		//if (elapset() > 1000 * 1000 * 1000 / FPS)
		//{
		//	start = high_resolution_clock::now();      // 計測スタート時刻を保存
		//	return true;
		//}

#pragma endregion

		System::Sleep((int32)sleepTime);	// 保険のスリープ
		while (elapset() < 1000 * 1000 * 1000 / FPS); //16

		start = high_resolution_clock::now();      // 計測スタート時刻を保存

		return System::Update();
	}
};
/// @brief System::Sleep(int32 millisecond)
/// 指定したミリ秒待つ
/// @param millisecond ミリ秒
void Sleep(int32 millisecond)
{
	System::Sleep(millisecond);
}
void Sleep(Duration& duration)
{
	System::Sleep(duration);
}
/// <summary>終了</summary>
void Exit()
{
	System::Exit();
}

bool startSysytem = { System2::Initialize() };

#define System System2
constexpr auto S3D_SYSTEM = "s3d::System を使いたい場合は、#undef System してください";
#define S3D_SYSTEM_NO_USE using System = System2;

