// #include "Extension\DirectX11\DXGraphics11.hpp"
#include "StdAfx.h"
#include "GameMain.h"

/// <summary>
/// Allows the game to perform any initialization it needs to before starting to run.
/// This is where it can query for any required services and load all of your content.
/// Initialize will enumerate through any components and initialize them as well.
/// </summary>
bool GameMain::Initialize()
{
	// TODO: Add your initialization logic here
	WindowTitle(_T("ES Game Library"));
	night = GraphicsDevice.CreateSpriteFromFile(_T("night.png"));
	enemy = GraphicsDevice.CreateSpriteFromFile(_T("samurai.png"));
	player = GraphicsDevice.CreateSpriteFromFile(_T("nin.png"), Color(255, 255, 255));
	leftplayer = GraphicsDevice.CreateSpriteFromFile(_T("nin2.png"), Color(255, 255, 255));
	kunai = GraphicsDevice.CreateSpriteFromFile(_T("kunai.png"), Color(255, 255, 255));
	sword = GraphicsDevice.CreateSpriteFromFile(_T("katana.png"), Color(255, 255, 255));
	sword2 = GraphicsDevice.CreateSpriteFromFile(_T("katana2.png"), Color(255, 255, 255));


	chara_x = 0; chara_y = 514;
	sword_x = chara_x + 100, sword_y = chara_y - 40;
	sword2_x = chara_x - 100, sword2_y = chara_y - 40;

	player_state = 0, jump_state = 0; hit_state = 0; shot_count = 0;
	jumpspeed = 0; jumptime = 0; zahyou = 0; sword_flag = false;

	enemy_x = 1100.0f;
	enemy_y = 500.0f;
	speed = 2.0f;

	enemy_move_flg = false;

	for (int i = 0; i < SHOT_MAX; i++)
	{
		shot_flg[i] = 0.0f;
		shot_x[i] = 0.0f;
		shot_y[i] = 0.0f;
	}

	return true;
}

/// <summary>
/// Finalize will be called once per game and is the place to release
/// all resource.
/// </summary>
void GameMain::Finalize()
{
	// TODO: Add your finalization logic here

}





/// <summary>
/// Allows the game to run logic such as updating the world,
/// checking for collisions, gathering input, and playing audio.
/// </summary>
/// <returns>
/// Scene continued value.
/// </returns>
int GameMain::Update()
{
	// TODO: Add your update logic here

}
/// <summary>
/// This is called when the game should draw itself.
/// </summary>
void GameMain::Draw()
{
	// TODO: Add your drawing code here
	GraphicsDevice.Clear(Color_CornflowerBlue);

	GraphicsDevice.BeginScene();


	SpriteBatch.Begin();


	SpriteBatch.End();

	GraphicsDevice.EndScene();



}