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
	kunai = GraphicsDevice.CreateSpriteFromFile(_T("kunai.png"),Color(255,255,255));
	kunai2 = GraphicsDevice.CreateSpriteFromFile(_T("kunai2.png"), Color(255, 255, 255));
	sword = GraphicsDevice.CreateSpriteFromFile(_T("katana.png"), Color(255, 255, 255));
	sword2 = GraphicsDevice.CreateSpriteFromFile(_T("katana2.png"), Color(255, 255, 255));


	chara_x = 0; chara_y = 540;
	sword_x = chara_x + 100, sword_y = chara_y - 40;
	sword2_x = chara_x - 100,sword2_y = chara_y - 40;

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
	//敵往復移動
		if (enemy_move_flg == false)
		{
			enemy_x = enemy_x - speed;
			if (enemy_x < 450) { enemy_x = 450; enemy_move_flg = true; }

		}
		if (enemy_move_flg == true)
		{
			enemy_x = enemy_x + speed;
			if (enemy_x > 1200) { enemy_x = 1200; enemy_move_flg = false; }
		}
	
		//画面制限
		if (chara_x < 0) {
			chara_x = 0;
		}
	
		if (chara_x >= 670 && chara_y >= 540) {
			chara_x = 670;
			chara_y = 540;
		}

	//プレイヤー
	{
		MainPlayer();
	}

	return 0;
}
void GameMain::MainPlayer()
{
	KeyboardState Key = Keyboard->GetState();
	KeyboardBuffer Key_buf = Keyboard->GetBuffer();

	//移動
	if (Key.IsKeyDown(Keys_Left)) {
		player_state = 1;
		chara_x -= 6.0f;
	}
	if (Key.IsKeyDown(Keys_Right)) {
		player_state = 0;
		chara_x += 6.0f;
	}

	//武器(刀)
	if (Key_buf.IsPressed(Keys_Z)) {
		if (sword_flag == false) {
			sword_flag = true;
		}
	}
		if (Key_buf.IsReleased(Keys_Z)) {
			if (sword_flag == true) {
				sword_flag = false;
			}
		}

		//刀座標
		sword_x = chara_x + 100, sword_y = chara_y - 40;
		sword2_x = chara_x - 100, sword2_y = chara_y - 40;

		//刀　―　敵　当たり判定(仮段階なので画像サイズで当たり判定)
		if (sword_x > enemy_x + 99.0f || sword_x + 100.0f < enemy_x ||
			sword_y > enemy_y + 99.0f || sword_y + 150.0f < enemy_y) {
			// 当たっていない
		}
		else {
			// 当たっている
			if (Key.IsKeyDown(Keys_Z)) {
				hit_state = 1;
			}
		}

		if (sword2_x > enemy_x + 98.0f || sword2_x + 100.0f < enemy_x ||
			sword2_y > enemy_y + 98.0f || sword2_y + 150.0f < enemy_y) {
			// 当たっていない
		}
		else {
			// 当たっている
			if (Key.IsKeyDown(Keys_Z)) {
				hit_state = 1;
			}
		}

	//武器(クナイ)
	if (Key_buf.IsPressed(Keys_X))
	{
		for (int i = 0; i < SHOT_MAX; i++)
		{
			if (shot_flg[i] == 0 && shot_count < 10)
			{
				shot_flg[i] = 1;
				shot_x[i] = chara_x + 60;
				shot_y[i] = chara_y + 30;
				break;
			}
		}
		shot_count += 1;
	}

		//当たり判定(現在制作中)
	for (int i = 0; i < SHOT_MAX; i++) {
		if (shot_flg[i] == 1) {
		if (shot_x[i] > enemy_x + 80.0f || shot_x[i] + 139.0f < enemy_x ||
			shot_y[i] > enemy_y + 31.0f || shot_y[i] + 69.0f < enemy_y) {
				// 当たっていない
			}
			else {
				// 当たっている
				hit_state = 1;
			}
		}
	}

	//ジャンプ
	if (jump_state == 0) {
		if (Key_buf.IsPressed(Keys_Space)) {

			zahyou = chara_y;
			jumpspeed = 20;
			jumptime = 0;
			jump_state = 1;
		}
	}
	if (jump_state == 1) {
		if (Key.IsKeyDown(Keys_Space)) {
			zahyou = chara_y;
			jumpspeed += 0.1;
			jump_state = 1;
			if (jumpspeed >= 20) {
				jumpspeed = 20;
				jump_state = 1;
			}
		}
	}

	if (jump_state == 1) {
		jumptime = jumptime + 0.15;

		chara_y = zahyou - (jumpspeed * jumptime - 0.5 * 9.80665 * jumptime * jumptime);

		if (chara_y >= 540) {
			chara_y = 540;
			jump_state = 0;
		}
	}

	//クナイ発射
	for (int i = 0; i < SHOT_MAX; i++)
	{
		if (shot_flg[i] == 1 && player_state == 0)
		{
			shot_x[i] += 35.0f;
			if (shot_x[i] > 1280)
			{
				shot_flg[i] = 0;
			}
		}
		if (shot_flg[i] == 1 && player_state == 1)
		{
			shot_x[i] -= 35.0f;
			if (shot_x[i]  < 0)
			{
				shot_flg[i] = 0;
			}
		}
	}
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

	if (player_state == 0) { SpriteBatch.Draw(*player, Vector3(chara_x, chara_y, -1)); }
	if (player_state == 1) { SpriteBatch.Draw(*leftplayer, Vector3(chara_x, chara_y, -1)); }


	for (int i = 0; i < SHOT_MAX; i++)
	{
		if (shot_flg[i] == 1 && player_state == 0) { SpriteBatch.Draw(*kunai, Vector3(shot_x[i], shot_y[i], -1)); }
		if (shot_flg[i] == 1 && player_state == 1) { SpriteBatch.Draw(*kunai2, Vector3(shot_x[i], shot_y[i], -1)); }
	}

	if (player_state == 0 && sword_flag == true) { SpriteBatch.Draw(*sword, Vector3(sword_x, sword_y, -1)); }
	if (player_state == 1 && sword_flag == true) { SpriteBatch.Draw(*sword2, Vector3(sword2_x, sword2_y, -1)); }

	SpriteBatch.Draw(*night, Vector3(0.0f, 0.0f, 0.0f));

	if (enemy_move_flg == false && hit_state == 0)
	{
		SpriteBatch.Draw(*enemy, Vector3(enemy_x, enemy_y, -1.0f));
	}
	if (enemy_move_flg == true && hit_state == 0)
	{
		SpriteBatch.Draw(*enemy, Vector3(enemy_x, enemy_y, -1.0f));
	}


	SpriteBatch.End();

	GraphicsDevice.EndScene();



}