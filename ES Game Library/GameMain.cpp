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
	_2F = GraphicsDevice.CreateSpriteFromFile(_T("2,4F.png"));
	enemy = GraphicsDevice.CreateSpriteFromFile(_T("samurai.png"));
	player = GraphicsDevice.CreateSpriteFromFile(_T("nin.png"), Color(255, 255, 255));
	leftplayer = GraphicsDevice.CreateSpriteFromFile(_T("nin2.png"), Color(255, 255, 255));
	kunai = GraphicsDevice.CreateSpriteFromFile(_T("kunai.png"), Color(255, 255, 255));
	kunai2 = GraphicsDevice.CreateSpriteFromFile(_T("kunai2.png"), Color(255, 255, 255));

	chara_x = 1100; chara_y = 550;
	kunai_x = chara_x, kunai_y = chara_y; //攻撃用クナイの初期座標
	kunai2_x = chara_x, kunai2_y = chara_y;
	floor2_1x = 1280.0f * 2; //背景のスクロール

	player_state = 1, jump_state = 0; hit_state = 0; shot_count = 0;
	jumpspeed = 0; jumptime = 0; zahyou = 0; kunai_flag = false;

	enemy_x = 1100.0f;
	enemy_y = 530.0f;
	speed = 2.0f;

	enemy_move_flg = false;


	return true;
}
//2と4ステ
void GameMain::Initialize_2_4()
{//2と4ステ

	floor = GraphicsDevice.CreateSpriteFromFile(_T("floor.png"));
	kaidan = GraphicsDevice.CreateSpriteFromFile(_T("kaidan2.png"));
	enemy = GraphicsDevice.CreateSpriteFromFile(_T("samurai.png"));
	player = GraphicsDevice.CreateSpriteFromFile(_T("nin.png"), Color(255, 255, 255));
	leftplayer = GraphicsDevice.CreateSpriteFromFile(_T("nin2.png"), Color(255, 255, 255));
	kunai = GraphicsDevice.CreateSpriteFromFile(_T("kunai.png"), Color(255, 255, 255));
	kunai2 = GraphicsDevice.CreateSpriteFromFile(_T("kunai2.png"), Color(255, 255, 255));

	chara_x = 1100; chara_y = 550;
	kunai_x = chara_x, kunai_y = chara_y; //攻撃用クナイの初期座標
	kunai2_x = chara_x, kunai2_y = chara_y;
	floor2_0x = 1280.0f; floor2_1x = 0; floor2_2x = -1280.0f; kaidan2_x = -1280.0f * 2;//背景のスクロール

	player_state = 1, jump_state = 0; hit_state = 0; shot_count = 0;
	jumpspeed = 0; jumptime = 0; zahyou = 0; kunai_flag = false;

	enemy_x = 1100.0f;
	enemy_y = 530.0f;
	speed = 2.0f;
	enemy_move_flg = false;
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
		if (enemy_x < 450) { enemy_x = 450; enemy_move_flg = true; }

	}
	if (enemy_move_flg == true)
	{
		enemy_x = enemy_x + speed;
		if (enemy_x > 1200) { enemy_x = 1200; enemy_move_flg = false; }
	}

//プレイヤー移動制限
	if (chara_x < 0) {
		chara_x = 0;
	}
	if (chara_x > 1150) {
		chara_x = 1150;
	}
	if (chara_y > 550){
		chara_y = 550;
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
	if (Key.IsKeyDown(Keys_A)) {
		player_state = 1;
		chara_x -= 6.0f;
		floor2_0x += 6.0f;
		floor2_1x += 6.0f;
		floor2_2x += 6.0f;
		kaidan2_x += 6.0f;
	}

	//背景移動制限
	if (kaidan2_x < -1280 * 2) {
		floor2_0x = 1280.0f; floor2_1x = 0.0f; floor2_2x = -1280.0f;  kaidan2_x = -1280 * 2;
	}
	if (kaidan2_x > 0) {
		floor2_0x = 1280 * 3;	floor2_1x = 1280 * 2; floor2_2x = 1280; kaidan2_x = 0.0f;
	}
	//武器(攻撃用クナイ)
	if (Key_buf.IsPressed(Keys_Z)) {
		if (kunai_flag == false) {
			kunai_flag = true;
		}
	}
	if (Key_buf.IsReleased(Keys_Z)) {
		if (kunai_flag == true) {
			kunai_flag = false;
		}
	}
	//攻撃用クナイ座標
	kunai_x = chara_x + 80, kunai_y = chara_y + 50;
	kunai2_x = chara_x - 10, kunai2_y = chara_y + 50;
	if (chara_x < 0) {
		chara_x = 0;
	}
	if (chara_x > 1150) {
		chara_x = 1150;
	}

	//敵　―　攻撃用クナイ
	if (kunai_x > enemy_x + 52.0f || kunai_x + 8.0f < enemy_x ||
		kunai_y > enemy_y + 73.0f || kunai_y + 5.0f < enemy_y) {
		// 当たっていない
	}
	else {
		// 当たっている
		if (Key.IsKeyDown(Keys_Z)) {
			hit_state = 1;
		}
	}
	if (kunai2_x > enemy_x + 52.0f || kunai2_x + 8.0f < enemy_x ||
		kunai2_y > enemy_y + 73.0f || kunai2_y + 5.0f < enemy_y) {
		// 当たっていない
	}
	else {
		// 当たっている
		if (Key.IsKeyDown(Keys_Z)) {
			hit_state = 1;
		}

	}
	//敵　―　プレイヤー当たり判定(敵を複数表示する予定。)(その時はforで処理をする)
	if (hit_state == 0) {
		if (chara_x > enemy_x + 70.0f - 30.0f || chara_x + 96.0f - 30.0f < enemy_x ||
			chara_y > enemy_y + 130.0f - 21.0f || chara_y + 100.0f - 30.0f < enemy_y) {
			// 当たっていない
		}
		else {
			// 当たっている

		}
	}
	// ジャンプ
	/*if (jump_state == 0) {
		if (Key_buf.IsPressed(Keys_W)) {

			zahyou = chara_y;
			jumpspeed = 25;
			jumptime = 0;
			jump_state = 1;
		}
	}
	if (jump_state == 1) {
		zahyou = chara_y;
		jumpspeed += 0.1;
		jump_state = 1;
		if (jumpspeed >= 25) {
			jumpspeed = 25;
			jump_state = 1;
		}
	}
	if (jump_state == 1) {
		jumptime = jumptime + 0.25;

		chara_y = zahyou - (jumpspeed * jumptime - 0.5 * 9.80665 * jumptime * jumptime);

		if (chara_y > 580) {
			chara_y = 580;
			jump_state = 0;
		}
	}*/
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

	if (player_state == 0) { SpriteBatch.Draw(*player, Vector3(chara_x, chara_y, -1)); }
	if (player_state == 1) { SpriteBatch.Draw(*leftplayer, Vector3(chara_x, chara_y, -1)); }

	if (player_state == 0 && kunai_flag == true) { SpriteBatch.Draw(*kunai, Vector3(kunai_x, kunai_y, -1)); }
	if (player_state == 1 && kunai_flag == true) { SpriteBatch.Draw(*kunai2, Vector3(kunai2_x, kunai2_y, -1)); }

	SpriteBatch.Draw(*_2F, Vector3(floor2_1x, 0.0f, 0.0f));


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

}//2と4ステ
void GameMain::Draw_2_4()
{//2と4ステ
	if (player_state == 0) { SpriteBatch.Draw(*player, Vector3(chara_x, chara_y, -1)); }
	if (player_state == 1) { SpriteBatch.Draw(*leftplayer, Vector3(chara_x, chara_y, -1)); }


	for (int i = 0; i < SHOT_MAX; i++)
	{
		if (shot_flg[i] == 1 && player_state == 0) { SpriteBatch.Draw(*kunai, Vector3(shot_x[i], shot_y[i], -1)); }
		if (shot_flg[i] == 1 && player_state == 1) { SpriteBatch.Draw(*kunai2, Vector3(shot_x[i], shot_y[i], -1)); }
	}

	if (player_state == 0 && kunai_flag == true) { SpriteBatch.Draw(*kunai, Vector3(kunai_x, kunai_y, -1)); }
	if (player_state == 1 && kunai_flag == true) { SpriteBatch.Draw(*kunai2, Vector3(kunai2_x, kunai2_y, -1)); }

	SpriteBatch.Draw(*floor, Vector3(floor2_0x, 0.0f, 0.0f));
	SpriteBatch.Draw(*floor, Vector3(floor2_1x, 0.0f, 0.0f));
	SpriteBatch.Draw(*floor, Vector3(floor2_2x, 0.0f, 0.0f));


	SpriteBatch.DrawString(text, Vector2(100, 10), Color_Black, _T("%.0f秒"), time);

	if (enemy_move_flg == false && hit_state == 0)
	{
		SpriteBatch.Draw(*enemy, Vector3(enemy_x, enemy_y, -1.0f));
	}
	if (enemy_move_flg == true && hit_state == 0)
	{
		SpriteBatch.Draw(*enemy, Vector3(enemy_x, enemy_y, -1.0f));
	}
	//ここまで2と4ステ
}

