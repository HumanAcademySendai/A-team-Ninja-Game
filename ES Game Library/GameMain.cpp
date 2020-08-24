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
	floor = GraphicsDevice.CreateSpriteFromFile(_T("1,3F.png"));
	kaidan = GraphicsDevice.CreateSpriteFromFile(_T("階段3.png"));
	enemy = GraphicsDevice.CreateSpriteFromFile(_T("samurai.png"));
	player = GraphicsDevice.CreateAnimationModelFromFile(_T("nin3_walk.0001.png"));
	leftplayer = GraphicsDevice.CreateAnimationModelFromFile(_T("nin3_walk.0001.png"));
	kunai = GraphicsDevice.CreateSpriteFromFile(_T("kunai.png"), Color(255, 255, 255));
	player_jump = GraphicsDevice.CreateModelFromFile(_T("nin_Jump.png"));

	player->SetScale(1, -1, 1);
	chara_x = 0; chara_y = 514;
	player->SetPosition(chara_x, chara_y, 0);
	leftplayer->SetScale(1, -1, 1);
	leftplayer->SetPosition(chara2_x, chara2_y, 0);
	leftplayer->SetRotation(90, 0, 0);

	camera->SetView(Vector3(0, 0, -10), Vector3(0, 0, 0));
	camera->SetOrthographicOffCenter(0, 1280, 720, 0, -10000, 10000);
	GraphicsDevice.SetCamera(camera);

	Light light;
	light.Type = Light_Directional;
	light.Direction = Vector3(0, 1, 1);
	light.Ambient = Color(1.0f, 1.0f, 1.0f);
	light.Diffuse = Color(1.0f, 1.0f, 1.0f);
	light.Specular = Color(1.0f, 1.0f, 1.0f);
	GraphicsDevice.SetLight(light);

	kunai2 = GraphicsDevice.CreateSpriteFromFile(_T("kunai2.png"), Color(255, 255, 255));

	chara_x = 0; chara_y = 550;
	kunai_x = chara_x, kunai_y = chara_y; //攻撃用クナイの初期座標
	kunai2_x = chara_x, kunai2_y = chara_y;
	floor1_0x = -1280.0f; floor1_1x = 0; floor1_2x = 1280.0f; kaidan1_x = 1280.0f * 2;//背景のスクロール

	player_state = 0, jump_state = 0; hit_state = 0; shot_count = 0;
	jumpspeed = 0; jumptime = 0; zahyou = 0; kunai_flag = false;

	enemy_x = 1100.0f;
	enemy_y = 530.0f;
	speed = 2.0f;
	hp_x = 200;
	hp_count = 192;
	enemyhit_count == 0;

	enemy_move_flg = false;

	Title = GraphicsDevice.CreateSpriteFromFile(_T("タイトル画面（修正）.png"));
	GameOver = GraphicsDevice.CreateSpriteFromFile(_T("ゲームオーバー.png"));
	Last = GraphicsDevice.CreateSpriteFromFile(_T("大広間.png"));
	hp1 = GraphicsDevice.CreateSpriteFromFile(_T("HPアイコン (1).png"));
	
	

	//ワープクナイ初期位置
	for (int i = 0; i < SHOT_MAX; i++)
	{
		shot_flg[i] = 0.0f;
		shot_x[i] = 0.0f;
		shot_y[i] = 0.0f;
	}

	gamescene == 0;

	return true;
}

void GameMain::steage2()
{
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
	if (chara_y > 550) {
		chara_y = 550;
	}

	KeyboardState Key = Keyboard->GetState();
	KeyboardBuffer Key_buf = Keyboard->GetBuffer();

	//移動
	if (Key.IsKeyDown(Keys_Right)) {
		player_state = 1;
		chara_x -= 6.0f;
		floor2_0x += 6.0f;
		floor2_1x += 6.0f;
		floor2_2x += 6.0f;
		kaidan2_x += 6.0f;
	}
	if (Key.IsKeyDown(Keys_Left)) {
		player_state = 0;
		chara_x += 6.0f;
		floor2_0x -= 6.0f;
		floor2_1x -= 6.0f;
		floor2_2x -= 6.0f;
		kaidan2_x -= 6.0f;

	}
	//背景移動制限
	if (kaidan2_x < -1280 * 2) {
		floor2_0x = 1280.0f; floor2_1x = 0.0f; floor2_2x = -1280.0f;  kaidan2_x = -1280 * 2;
	}
	if (kaidan2_x > 0) {
		floor2_0x = 1280 * 3;	floor2_1x = 1280 * 2; floor2_2x = 1280; kaidan2_x = 0.0f;
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
	kunai_x = chara_x + 80, kunai_y = chara_y + 50;
	kunai2_x = chara_x - 10, kunai2_y = chara_y + 50;



	//敵　―　攻撃用クナイ
	if (kunai_x > enemy_x + 52.0f || kunai_x + 8.0f < enemy_x ||
		kunai_y > enemy_y + 73.0f || kunai_y + 5.0f < enemy_y) {
		// 当たっていない
	}
	else {
		// 当たっている
		if (Key.IsKeyDown(Keys_Space)) {
			hit_state = 1;
		}
	}

	if (kunai2_x > enemy_x + 52.0f || kunai2_x + 8.0f < enemy_x ||
		kunai2_y > enemy_y + 73.0f || kunai2_y + 5.0f < enemy_y) {
		// 当たっていない
	}
	else {
		// 当たっている
		if (Key.IsKeyDown(Keys_Space)) {
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


	//武器(ワープクナイ)
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

	//当たり判定(未完成)(橋本君のプログラムをちょっと手を加えたらワープクナイできそうなのでそちらを使ってください)
//for (int i = 0; i < SHOT_MAX; i++) {
//	if (shot_flg[i] == 1) {
//	if (shot_x[i] > enemy_x + 80.0f || shot_x[i] + 139.0f < enemy_x ||
//		shot_y[i] > enemy_y + 31.0f || shot_y[i] + 69.0f < enemy_y) {
//			// 当たっていない
//		}
//		else {
//			// 当たっている
//			hit_state = 1;
//		}
//	}
//}


// ジャンプ
	if (jump_state == 0) {
		if (Key_buf.IsPressed(Keys_Up)) {

			zahyou = chara_y;
			jumpspeed = 25;
			jumptime = 0;
			jump_state = 1;
			
		}
	}
	if (player_jump_flg == false) {
		player_jump->Rotation(90, 0, 0);
		if (Key.IsKeyDown(Keys_Left)) {
			player_jump_flg = true;
		}
	}
	if (player_jump_flg == true) {
		if (Key.IsKeyDown(Keys_Right)) {
			player_jump_flg = false;
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
	}

	//ワープクナイ発射
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
			if (shot_x[i] < 0)
			{
				shot_flg[i] = 0;
			}
		}
	}
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
		MainPlayer();
	}

	return 0;
}
void GameMain::MainPlayer()
{
	KeyboardState Key = Keyboard->GetState();
	KeyboardBuffer Key_buf = Keyboard->GetBuffer();

	//移動
	if (Key.IsKeyDown(Keys_Right)) {
		player_state = 1;
		chara_x -= 6.0f;
		floor1_0x += 6.0f;
		floor1_1x += 6.0f;
		floor1_2x += 6.0f;
		kaidan1_x += 6.0f;
	}
	if (Key.IsKeyDown(Keys_Left)) {
		player_state = 0;
		chara_x += 6.0f;
		floor1_0x -= 6.0f;
		floor1_1x -= 6.0f;
		floor1_2x -= 6.0f;
		kaidan1_x -= 6.0f;
	}

	//背景移動制限
	if (chara_x < 0) {
		floor1_0x = -1280;	floor1_1x = 0; floor1_2x = 1280; kaidan1_x = 2560;
	}
	if (kaidan1_x < 0) {
		floor1_0x =- 1280.0f * 3; floor1_1x = -1280.0f * 2; floor1_2x = -1280.0f;  kaidan1_x = 0;
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
	kunai_x = chara_x + 80, kunai_y = chara_y + 50;
	kunai2_x = chara_x - 10, kunai2_y = chara_y + 50;



	//敵　―　攻撃用クナイ
	if (kunai_x > enemy_x + 52.0f || kunai_x + 8.0f < enemy_x ||
		kunai_y > enemy_y + 73.0f || kunai_y + 5.0f < enemy_y) {
		// 当たっていない
	}
	else {
		// 当たっている
		if (Key.IsKeyDown(Keys_Space)) {
			hit_state = 1;
		}
	}

	if (kunai2_x > enemy_x + 52.0f || kunai2_x + 8.0f < enemy_x ||
		kunai2_y > enemy_y + 73.0f || kunai2_y + 5.0f < enemy_y) {
		// 当たっていない
	}
	else {
		// 当たっている
		if (Key.IsKeyDown(Keys_Space)) {
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
			enemyhit_count += 1;
			hp_count = 192 - (60 + 3 * enemyhit_count);
		}
	}

	//武器(ワープクナイ)
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

	//当たり判定(未完成)(橋本君のプログラムをちょっと手を加えたらワープクナイできそうなのでそちらを使ってください)
//for (int i = 0; i < SHOT_MAX; i++) {
//	if (shot_flg[i] == 1) {
//	if (shot_x[i] > enemy_x + 80.0f || shot_x[i] + 139.0f < enemy_x ||
//		shot_y[i] > enemy_y + 31.0f || shot_y[i] + 69.0f < enemy_y) {
//			// 当たっていない
//		}
//		else {
//			// 当たっている
//			hit_state = 1;
//		}
//	}
//}


// ジャンプ
	if (jump_state == 0) {
		if (Key_buf.IsPressed(Keys_Up)) {

			zahyou = chara_y;
			jumpspeed = 25;
			jumptime = 0;
			jump_state = 1;
		}
	}
	if (player_jump_flg == false) {
		player_jump->Rotation(90, 0, 0);
		if (Key.IsKeyDown(Keys_Left)) {
			player_jump_flg = true;
		}
	}
	if (player_jump_flg == true) {
		if (Key.IsKeyDown(Keys_Right)) {
			player_jump_flg = false;
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
	}

	//ワープクナイ発射
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
			if (shot_x[i] < 0)
			{
				shot_flg[i] = 0;
			}
		}
	}
}

void GameMain::scene_change()
{

}
/// <summary>
/// This is called when the game should draw itself.
/// </summary>
void GameMain::Draw()
{
	// TODO: Add your drawing code here
	GraphicsDevice.Clear(Color_CornflowerBlue);

	GraphicsDevice.BeginScene();
	player->SetPosition(chara_x, chara_y, 0);
	player->Draw();
	player->AdvanceTime(GameTimer.GetElapsedSecond());
	GraphicsDevice.SetCamera(camera);

	SpriteBatch.Begin();
	if (gamescene = 1) {
		
	/*	if (player_state == 1) { SpriteBatch.Draw(*leftplayer, Vector3(chara_x, chara_y, -1)); }*/

		SpriteBatch.Draw(*hp1, Vector3(hp_x, 0, 0), RectWH(0, 0, hp_count, 60));

		for (int i = 0; i < SHOT_MAX; i++)
		{
			if (shot_flg[i] == 1 && player_state == 0) { SpriteBatch.Draw(*kunai, Vector3(shot_x[i], shot_y[i], -1)); }
			if (shot_flg[i] == 1 && player_state == 1) { SpriteBatch.Draw(*kunai2, Vector3(shot_x[i], shot_y[i], -1)); }
		}

		if (player_state == 0 && kunai_flag == true) { SpriteBatch.Draw(*kunai, Vector3(kunai_x, kunai_y, -1)); }
		if (player_state == 1 && kunai_flag == true) { SpriteBatch.Draw(*kunai2, Vector3(kunai2_x, kunai2_y, -1)); }

		SpriteBatch.Draw(*floor, Vector3(floor1_0x, 0.0f, 0.0f));
		SpriteBatch.Draw(*floor, Vector3(floor1_1x, 0.0f, 0.0f));
		SpriteBatch.Draw(*floor, Vector3(floor1_2x, 0.0f, 0.0f));
		SpriteBatch.Draw(*kaidan, Vector3(kaidan1_x, 0.0f, 0.0f));

		if (enemy_move_flg == false && hit_state == 0)
		{
			SpriteBatch.Draw(*enemy, Vector3(enemy_x, enemy_y, -1.0f));
		}
		if (enemy_move_flg == true && hit_state == 0)
		{
			SpriteBatch.Draw(*enemy, Vector3(enemy_x, enemy_y, -1.0f));
		}
	}
	if (gamescene = 0) {
		SpriteBatch.Draw(*Title, Vector3(0, 0, 0));
	}
	if (gamescene = 2) {
		SpriteBatch.Draw(*GameOver, Vector3(0, 0, 0));
	}
	if (gamescene = 3) {
		SpriteBatch.Draw(*Last, Vector3(0, 0, 0));
	}

	SpriteBatch.End();


	GraphicsDevice.EndScene();



}