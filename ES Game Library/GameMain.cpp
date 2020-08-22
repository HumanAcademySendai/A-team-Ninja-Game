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
	//1と3


	Game_scene_flg = false;

	if (Game_scene_flg = true)
	{
       Initialize_1_3();
	}
	
	    

	
	/*Game_scene_flg2 = false;*/
	return true;
}

//1と3ステ
void GameMain::Initialize_1_3()
{ //1と3ステ
		floor = GraphicsDevice.CreateSpriteFromFile(_T("1,3F.png"));
		enemy = GraphicsDevice.CreateSpriteFromFile(_T("samurai.png"));
		player = GraphicsDevice.CreateSpriteFromFile(_T("nin.png"), Color(255, 255, 255));
		kunai = GraphicsDevice.CreateSpriteFromFile(_T("kunai.png"), Color(255, 255, 255));
		kunai2 = GraphicsDevice.CreateSpriteFromFile(_T("kunai2.png"), Color(255, 255, 255));
		Space = GraphicsDevice.CreateSpriteFromFile(_T("攻撃(Space).png"));
		Right = GraphicsDevice.CreateSpriteFromFile(_T("移動(右).png"));
		Up = GraphicsDevice.CreateSpriteFromFile(_T("ジャンプ(上).png"));

		chara_x = 0; chara_y = 530; time = 0; frame = 0;
		kunai_x = chara_x, kunai_y = chara_y; //攻撃用クナイの初期座標
		floor1_1x = 0;//背景のスクロール
		floor1_1y = 0; kaidan1_x = 1000;
		player_state = 0, jump_state = 0; hit_enemy_state = 0; hit_enemy2_state = 0; jump_enemy_state = 0;
		jumpspeed = 0; jumptime = 0; zahyou = 0;  kunai_flag = false;
		enemy_jumpspeed = 0; enemy_jumptime = 0; enemy_zahyou = 0;
		player_hit_state = 0;

		enemy_x =  400.0f;
		enemy_y = 530.0f;
		 enemy_x2 = 850.0f;
		enemy_y2 = 530.0f;

		speed = 1.0f;

		text = GraphicsDevice.CreateSpriteFont(_T("游明朝 Demibold"), 60);
		text2 = GraphicsDevice.CreateSpriteFont(_T("游明朝 Demibold"), 30);

		enemy_move_flg = false;
		enemy_move_flg2 = false;
		//ここまで1と3ステ
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
		if (enemy_x < 300) { enemy_x =300; enemy_move_flg = true; }

	}
	if (enemy_move_flg == true)
	{
		enemy_x = enemy_x + speed;
		if (enemy_x > 400) { enemy_x = 400; enemy_move_flg = false; }
	}
	if (enemy_move_flg2 == false)
	{
		enemy_x2 = enemy_x2 - speed;
		if (enemy_x2 < 650) { enemy_x2 = 650; enemy_move_flg2 = true; }
	}
	if (enemy_move_flg2 == true)
	{
		enemy_x2 = enemy_x2 + speed;
		if (enemy_x2 > 750) { enemy_x2 = 750; enemy_move_flg2 = false; }
	}
	

	//プレイヤー&&プレイヤー移動制限

	MainPlayer_1_3();
	

	return 0;
}
//1と3ステ
void GameMain::MainPlayer_1_3()
{   //1と3ステ
	
		KeyboardState Key = Keyboard->GetState();
		KeyboardBuffer Key_buf = Keyboard->GetBuffer();
		//移動
		

		
		if (Key.IsKeyDown(Keys_Right)) {
			player_state = 0;
			chara_x += 6.0f;
			floor1_1x -= 12.0f;

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
			//jumpspeed -= 2;
			jumptime = jumptime + 0.25;

			chara_y -= jumpspeed;

			chara_y = zahyou - (jumpspeed * jumptime - 0.5 * 9.80665 * jumptime * jumptime);

			if (chara_y > 530) {
				chara_y = 530;
				jump_state = 0;
			}
		}

		// ジャンプ
		if (jump_enemy_state == 0) {
			if (Key_buf.IsPressed(Keys_Up)) {

				enemy_zahyou = enemy_y;
				enemy_jumpspeed = 60;
				enemy_jumptime = 0;
				jump_enemy_state = 1;
			}
		}
		if (jump_enemy_state == 1) {
			if (Key.IsKeyDown(Keys_Up)) {
				if (enemy_jumpspeed >= 60) {
					enemy_jumpspeed = 60;
				}
			}
			//jumpspeed -= 2;
			enemy_jumptime = enemy_jumptime + 0.25;

			enemy_y -= enemy_jumpspeed;

			enemy_y = zahyou - (enemy_jumpspeed * enemy_jumptime - 0.5 * 9.80665 * enemy_jumptime * enemy_jumptime);

			if (enemy_y > 530) {
				enemy_y = 530;
				jump_enemy_state = 0;
			}
		}

		//タイム(カウントアップ)
		if (time < 10000) {
			frame += 1;
			if (frame >= 60) {
				time += 1;
				frame = 0;
			}
		}

		//背景移動制限
		if (chara_x < 0) {
			floor1_1x = 0;
		}
		if (floor1_1x < -2560) {
			floor1_1x = -2560;
		}
		if (floor1_1x > -5) {
			chara_x = 0;
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
		kunai_x = chara_x + 100, kunai_y = chara_y + 50;
		//敵　―　攻撃用クナイ
		if (kunai_x > enemy_x + 52.0f || kunai_x + 8.0f < enemy_x ||
			kunai_y > enemy_y + 73.0f || kunai_y + 5.0f < enemy_y) {
			// 当たっていない
		}
		else {
			// 当たっている
			if (Key.IsKeyDown(Keys_Space)) {
				hit_enemy_state = 1;
			}
		}

		//敵　―　攻撃用クナイ
		if (kunai_x > enemy_x2 + 52.0f || kunai_x + 8.0f < enemy_x2 ||
			kunai_y > enemy_y2 + 73.0f || kunai_y + 5.0f < enemy_y2) {
			// 当たっていない
		}
		else {
			// 当たっている
			if (Key.IsKeyDown(Keys_Space)) {
				hit_enemy2_state = 2;
			}
		}

		//敵　―　プレイヤー当たり判定(敵を複数表示する予定。)
			if (chara_x > enemy_x + 70.0f - 30.0f || chara_x + 80.0f - 30.0f < enemy_x ||
				chara_y > enemy_y + 130.0f - 21.0f || chara_y + 110.0f - 10.0f < enemy_y) {
				// 当たっていない
			}
			else {
				// 当たっている
				player_hit_state = 1;
			}

			if (chara_x > enemy_x2 + 70.0f - 30.0f || chara_x + 80.0f - 30.0f < enemy_x2 ||
				chara_y > enemy_y2 + 130.0f - 21.0f || chara_y + 110.0f - 10.0f < enemy_y2) {
				// 当たっていない
			}
			else {
				// 当たっている
				player_hit_state = 1;
			}	

		//階段当たり判定
		if (chara_x > floor1_1x + 3440.0f || chara_x + 200.0f - 70.0f < floor1_1x + 2600||
			chara_y > floor1_1y + 550.0f || chara_y + 250.0f - 10.0f < floor1_1y) {

		}
		else {
			chara_y = -1.4f * chara_x + 1600;
			if (chara_y < 100.0f) {
				Game_scene_flg = false;
			
			}
		}

		if (chara_x < 0) {
			chara_x = 0;
		}
		if (chara_x > 1150) {
			chara_x = 1150;
		}
	}
		//ここまで1と3ステ





/// <summary>
/// This is called when the game should draw itself.
/// </summary>
void GameMain::Draw()
{
	// TODO: Add your drawing code here
	GraphicsDevice.Clear(Color_CornflowerBlue);

	GraphicsDevice.BeginScene();


	SpriteBatch.Begin();
	if (Game_scene_flg == true)
	{
	Draw_1_3();
    }
	
	SpriteBatch.End();


	GraphicsDevice.EndScene();

	//Canvas canvas = GraphicsDevice.LockCanvas();

	//Paint paint;
	//paint.SetPaintColor(Color_Yellow);
	//canvas.DrawRect(Rect(kunai_x + 0 ,kunai_y + 0, kunai_x + 8.0f, kunai_y + 5.0f), paint);


	//GraphicsDevice.UnlockCanvas();
}

//1と3ステ
void GameMain::Draw_1_3()
{  //1と3ステ
	
		if (player_state == 0) { SpriteBatch.Draw(*player, Vector3(chara_x, chara_y, -1)); }

		if (player_state == 0 && kunai_flag == true) { SpriteBatch.Draw(*kunai, Vector3(kunai_x, kunai_y, -1)); }

		SpriteBatch.Draw(*Right, Vector3(50, 100, -1));
		//SpriteBatch.DrawString(text2, Vector2(100, 100), Color_White, _T("・・・移動"));

		SpriteBatch.Draw(*Up, Vector3(50,160, -1));
		//SpriteBatch.DrawString(text2, Vector2(300, 160), Color_White, _T("・・・ジャンプ"));

		SpriteBatch.Draw(*Space, Vector3(50, 225, -1));
		//SpriteBatch.DrawString(text, Vector2(300, 225), Color_Black, _T("・・・攻撃"));


		SpriteBatch.Draw(*floor, Vector3(floor1_1x, 0.0f, 0.0f));

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
		
		//敵とプレイヤーが当たった時の処理
		if (player_hit_state == 1) {
		
			player_hit_state = 0;
		}


		//ここまで1と3ステ
	}

