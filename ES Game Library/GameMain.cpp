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
	WindowTitle(_T("忍者　飛影"));

	Initialize_2_4();

	return true;
}
//2と4ステ
void GameMain::Initialize_2_4()
{//2と4ステ

	floor = GraphicsDevice.CreateSpriteFromFile(_T("2_4F.png"));
	enemy = GraphicsDevice.CreateSpriteFromFile(_T("samurai.png"));
	player = GraphicsDevice.CreateSpriteFromFile(_T("nin2.png"), Color(255, 255, 255));
	jump = GraphicsDevice.CreateSpriteFromFile(_T("nin_Jump.png"), Color(255, 255, 255));
	kunai = GraphicsDevice.CreateSpriteFromFile(_T("kunai.png"), Color(255, 255, 255));
	kunai2 = GraphicsDevice.CreateSpriteFromFile(_T("kunai2.png"), Color(255, 255, 255));
	Up = GraphicsDevice.CreateSpriteFromFile(_T("ジャンプ(上).png"));
	Left = GraphicsDevice.CreateSpriteFromFile(_T("移動(左).png"));
	Space = GraphicsDevice.CreateSpriteFromFile(_T("攻撃(Space).png"));
	
	chara_x = 1150; chara_y = 530; frame = 0; time = 0;//前ステージの秒数を引き継ぐ
	kunai_x = chara_x, kunai_y = chara_y; //攻撃用クナイの初期座標
	kunai2_x = chara_x, kunai2_y = chara_y;
	floor2_1x = -2560; floor2_1y = 0;//背景のスクロール
	enemyhit_count = 0;
	player_state = 1, jump_state = 0;
	hit_enemy_state = 0; hit_enemy2_state = 0; hit_enemy3_state = 0; hit_enemy4_state = 0;
	jumpspeed = 0; jumptime = 0; zahyou = 0; kunai_flag = false;
	
	enemy_jumpspeed = 0, enemy_jumptime = 0, enemy_zahyou = 0, enemy2_jumpspeed = 0, enemy2_jumptime = 0, enemy2_zahyou = 0;
	enemy3_jumpspeed = 0, enemy3_jumptime = 0, enemy3_zahyou = 0;
	jump_enemy_state = 0, jump_enemy2_state = 0, jump_enemy3_state = 0;

	enemy_x = 1000.0f;
	enemy_y = 530.0f;
	enemy_x2 = 800.0f;
	enemy_y2 = 530.0f;
	enemy_x3 = 600.0f;
	enemy_y3 = 530.0f;
	enemy_x4 = 400.0f;
	enemy_y4 = 530.0f;
	speed = 2.0f;
	enemy_move_flg = false;
	enemy_move_flg2 = false;
	enemy_move_flg3 = false;
	enemy_move_flg4 = false;

	text = GraphicsDevice.CreateSpriteFont(_T("游明朝 Demibold"), 60);

	//ここまで2と4ステ
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
		if (enemy_x < 900) { enemy_x = 900; enemy_move_flg = true; }

	}
	if (enemy_move_flg == true)
	{
		enemy_x = enemy_x + speed;
		if (enemy_x > 1000) { enemy_x = 1000; enemy_move_flg = false; }
	}

	if (enemy_move_flg2 == false)
	{
		enemy_x2 = enemy_x2 - speed;
		if (enemy_x2 < 750) { enemy_x2 = 750; enemy_move_flg2 = true; }

	}

	if (enemy_move_flg2 == true)
	{
		enemy_x2 = enemy_x2 + speed;
		if (enemy_x2 > 800) { enemy_x2 = 800; enemy_move_flg2 = false; }
	}

	if (enemy_move_flg3 == false)
	{
		enemy_x3 = enemy_x3 - speed;
		if (enemy_x3 < 400) { enemy_x3 = 400; enemy_move_flg3 = true; }

	}
	if (enemy_move_flg3 == true)
	{
		enemy_x3 = enemy_x3 + speed;
		if (enemy_x3 > 500) { enemy_x3 = 500; enemy_move_flg3 = false; }
	}

	if (enemy_move_flg4 == false)
	{
		enemy_x4 = enemy_x4 - speed;
		if (enemy_x4 < 200) { enemy_x4 = 200; enemy_move_flg4 = true; }

	}
	if (enemy_move_flg4 == true)
	{
		enemy_x4 = enemy_x4 + speed;
		if (enemy_x4 > 300) { enemy_x4 = 300; enemy_move_flg4 = false; }
	}

	//タイム(カウントアップ)
	if (time < 10000) {
		frame += 1;
		if (frame >= 60) {
			time += 1;
			frame = 0;
		}
	}

//プレイヤー移動制限
	if (chara_x < 20) {
		chara_x = 20;
	}
	if (chara_x > 1150) {
		chara_x = 1150;
	}
	if (chara_y > 530){
		chara_y = 530;
	}
	//プレイヤー
	{
		MainPlayer_2_4();
	}

	return 0;
}
//2と4ステ
void GameMain::MainPlayer_2_4()
{//2と4ステ
	KeyboardState Key = Keyboard->GetState();
	KeyboardBuffer Key_buf = Keyboard->GetBuffer();
	//移動
	if (Key.IsKeyDown(Keys_Left)) {
		player_state = 1;
		chara_x -= 6.0f;
		floor2_1x += 12.0f;

	}

	//背景移動制限
	if (floor2_1x > 0) {
		floor2_1x = 0;
	}

	//階段当たり判定
	if (chara_x > floor2_1x + 1300.0f || chara_x + 200.0f - 70.0f < floor2_1x ||
		chara_y > floor2_1y + 770.0f || chara_y + 250.0f - 10.0f < floor2_1y) {

	}
	else {
		//jump_enemy_state = 1, jump_enemy2_state = 1, jump_enemy3_state = 1;

		jump_state = 0;
		chara_y = 1.3 * chara_x;

		//接触したら最終ステージに移動するプログラム
		if (chara_y < 50) {

		}

	}

	//武器(攻撃用クナイ)
	if (Key_buf.IsPressed(Keys_Space)) {
		if (kunai_flag == false) {
			kunai_flag = true;
		}
	}
	if (Key_buf.IsReleased(Keys_Space)) {
		if (kunai_flag == true) {
			kunai_flag = false;
		}
	}

	//攻撃用クナイ座標
	kunai2_x = chara_x - 10, kunai2_y = chara_y + 60;
	if (chara_x < 0) {
		chara_x = 0;
	}
	if (chara_x > 1150) {
		chara_x = 1150;
	}

	//敵　―　攻撃用クナイ
	if (kunai2_x > enemy_x + 70.0f - 30.0f || kunai2_x + 8.0f < enemy_x ||
		kunai2_y > enemy_y + 130.0f - 21.0f || kunai2_y + 5.0f < enemy_y) {
		// 当たっていない
	}
	else {
		// 当たっている
		if (Key.IsKeyDown(Keys_Space)) {
			hit_enemy_state = 1;
		}

	}

	if (kunai2_x > enemy_x2 + 70.0f - 30.0f || kunai2_x + 8.0f < enemy_x2 ||
		kunai2_y > enemy_y2 + 130.0f - 21.0f || kunai2_y + 5.0f < enemy_y2) {
		// 当たっていない
	}
	else {
		// 当たっている
		if (Key.IsKeyDown(Keys_Space)) {
			hit_enemy2_state = 1;
		}

	}

	if (kunai2_x > enemy_x3 + 70.0f - 30.0f || kunai2_x + 8.0f < enemy_x3 ||
		kunai2_y > enemy_y3 + 130.0f - 21.0f || kunai2_y + 5.0f < enemy_y3) {
		// 当たっていない
	}
	else {
		// 当たっている
		if (Key.IsKeyDown(Keys_Space)) {
			hit_enemy3_state = 1;
		}

	}
	
	if (kunai2_x > enemy_x4 + 70.0f - 30.0f || kunai2_x + 8.0f < enemy_x4 ||
		kunai2_y > enemy_y4 + 130.0f - 21.0f || kunai2_y + 5.0f < enemy_y4) {
		// 当たっていない
	}
	else {
		// 当たっている
		if (Key.IsKeyDown(Keys_Space)) {
			hit_enemy4_state = 1;
		}

	}

	//敵　―　プレイヤー当たり判定(敵を複数表示する予定。)
	if (hit_enemy_state == 0){
		if (chara_x > enemy_x + 70.0f - 30.0f || chara_x + 128.0f - 70.0f < enemy_x ||
			chara_y > enemy_y + 130.0f - 21.0f || chara_y + 128.0f - 10.0f < enemy_y) {
			// 当たっていない
		}
		else {
			// 当たっている
			enemyhit_count = 1;

		}
	}

	if (hit_enemy2_state == 0) {
		if (chara_x > enemy_x2 + 70.0f - 30.0f || chara_x + 128.0f - 70.0f < enemy_x2 ||
			chara_y > enemy_y2 + 130.0f - 21.0f || chara_y + 128.0f - 10.0f < enemy_y2) {
			// 当たっていない
		}
		else {
			// 当たっている
			enemyhit_count  = 1;

		}
	}
	
	if (hit_enemy3_state == 0) {
		if (chara_x > enemy_x3 + 70.0f - 30.0f || chara_x + 128.0f - 70.0f < enemy_x3 ||
			chara_y > enemy_y3 + 130.0f - 21.0f || chara_y + 128.0f - 10.0f < enemy_y3) {
			// 当たっていない
		}
		else {
			// 当たっている
			enemyhit_count = 1;

		}
	}

	if (hit_enemy4_state == 0) {
		if (chara_x > enemy_x4 + 70.0f - 30.0f || chara_x + 128.0f - 70.0f < enemy_x4 ||
			chara_y > enemy_y4 + 130.0f - 21.0f || chara_y + 128.0f - 10.0f < enemy_y4) {
			// 当たっていない
		}
		else {
			// 当たっている
			enemyhit_count = 1;

		}
	}

	// ジャンプ
	if (jump_state == 0) {
		if (Key_buf.IsPressed(Keys_Up)) {

			zahyou = chara_y;
			jumpspeed = 60;
			jumptime = 0;
			jump_state = 1;
		}
	}
	if (jump_state == 1) {
		if (Key.IsKeyDown(Keys_Up)) {
			if (jumpspeed >= 60) {
				jumpspeed = 60;
			}
		}
		
		jumptime = jumptime + 0.25;

		chara_y -= jumpspeed;

		chara_y = zahyou - (jumpspeed * jumptime - 0.5 * 9.80665 * jumptime * jumptime);

		if (chara_y > 530) {
			chara_y = 530;
			jump_state = 0;
		}

		// 敵ジャンプ
		if (jump_enemy_state == 0) {
			if (Key_buf.IsPressed(Keys_Up)) {

				enemy_zahyou = enemy_y2;
				enemy_jumpspeed = 50;
				enemy_jumptime = 0;
				jump_enemy_state = 1;
			}
		}
		if (jump_enemy_state == 1) {
			if (Key.IsKeyDown(Keys_Up)) {
				if (enemy_jumpspeed >= 50) {
					enemy_jumpspeed = 50;
				}
			}

			enemy_jumptime = enemy_jumptime + 0.25;

			enemy_y2 -= enemy_jumpspeed;

			enemy_y2 = enemy_zahyou - (enemy_jumpspeed * enemy_jumptime - 0.5 * 9.80665 * enemy_jumptime * enemy_jumptime);

			if (enemy_y2 > 530) {
				enemy_y2 = 530;
				jump_enemy_state = 0;
			}
		}

		if (jump_enemy2_state == 0) {
			if (Key_buf.IsPressed(Keys_Up)) {

				enemy2_zahyou = enemy_y3;
				enemy2_jumpspeed = 40;
				enemy2_jumptime = 0;
				jump_enemy2_state = 1;
			}
		}
		if (jump_enemy2_state == 1) {
			if (Key.IsKeyDown(Keys_Up)) {
				if (enemy2_jumpspeed >= 40) {
					enemy2_jumpspeed = 40;
				}
			}

			enemy2_jumptime = enemy2_jumptime + 0.25;

			enemy_y3 -= enemy2_jumpspeed;

			enemy_y3 = enemy2_zahyou - (enemy2_jumpspeed * enemy2_jumptime - 0.5 * 9.80665 * enemy2_jumptime * enemy2_jumptime);

			if (enemy_y3 > 530) {
				enemy_y3 = 530;
				jump_enemy2_state = 0;
			}
		}

		if (jump_enemy3_state == 0) {
			if (Key_buf.IsPressed(Keys_Up)) {

				enemy3_zahyou = enemy_y4;
				enemy3_jumpspeed = 60;
				enemy3_jumptime = 0;
				jump_enemy3_state = 1;
			}
		}
		if (jump_enemy3_state == 1) {
			if (Key.IsKeyDown(Keys_Up)) {
				if (enemy3_jumpspeed >= 60) {
					enemy3_jumpspeed = 60;
				}
			}

			enemy3_jumptime = enemy3_jumptime + 0.25;

			enemy_y4 -= enemy3_jumpspeed;

			enemy_y4 = enemy3_zahyou - (enemy3_jumpspeed * enemy3_jumptime - 0.5 * 9.80665 * enemy3_jumptime * enemy3_jumptime);

			if (enemy_y4 > 530) {
				enemy_y4 = 530;
				jump_enemy3_state = 0;
			}
		}
	}
	//ここまで2と4ステ
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

	Draw_2_4();

	SpriteBatch.End();

	GraphicsDevice.EndScene();

}
//2と4ステ
void GameMain::Draw_2_4()
{//2と4ステ
	if (jump_state == 0) { SpriteBatch.Draw(*player, Vector3(chara_x, chara_y, -2)); }
	if (jump_state == 1) { SpriteBatch.Draw(*jump, Vector3(chara_x, chara_y, -2)); }

	if (player_state == 1 && kunai_flag == true) { SpriteBatch.Draw(*kunai2, Vector3(kunai2_x, kunai2_y, -2)); }

	SpriteBatch.Draw(*Left, Vector3(1000, 100, -2));

	SpriteBatch.Draw(*Up, Vector3(1000, 175, -2));

	SpriteBatch.Draw(*Space, Vector3(1000, 250,-2));

	SpriteBatch.Draw(*floor, Vector3(floor2_1x, 0.0f, 0));

	SpriteBatch.DrawString(text, Vector2(100, 10), Color_White, _T("%.0f秒"), time);

	if (enemy_move_flg == false && hit_enemy_state == 0)
	{
		SpriteBatch.Draw(*enemy, Vector3(enemy_x, enemy_y, -1.0f));
	}
	if (enemy_move_flg == true && hit_enemy_state == 0)
	{
		SpriteBatch.Draw(*enemy, Vector3(enemy_x, enemy_y, -1.0f));
	}

	if (enemy_move_flg2 == false && hit_enemy2_state == 0)
	{
		SpriteBatch.Draw(*enemy, Vector3(enemy_x2, enemy_y2, -1.0f));
	}
	if (enemy_move_flg2 == true && hit_enemy2_state == 0)
	{
		SpriteBatch.Draw(*enemy, Vector3(enemy_x2, enemy_y2, -1.0f));
	}

	if (enemy_move_flg3 == false && hit_enemy3_state == 0)
	{
		SpriteBatch.Draw(*enemy, Vector3(enemy_x3, enemy_y3, -1.0f));
	}
	if (enemy_move_flg3 == true && hit_enemy3_state == 0)
	{
		SpriteBatch.Draw(*enemy, Vector3(enemy_x3, enemy_y3, -1.0f));
	}

	if (enemy_move_flg4 == false && hit_enemy4_state == 0)
	{
		SpriteBatch.Draw(*enemy, Vector3(enemy_x4, enemy_y4, -1.0f));
	}
	if (enemy_move_flg4 == true && hit_enemy4_state == 0)
	{
		SpriteBatch.Draw(*enemy, Vector3(enemy_x4, enemy_y4, -1.0f));
	}
	//ここまで2と4ステ
}

