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

	//1ステ
	game_scene = 0;

	floor = GraphicsDevice.CreateSpriteFromFile(_T("1,3F.png"));
	enemy = GraphicsDevice.CreateSpriteFromFile(_T("samurai.png"), Color(255, 255, 255));
	ene_nin = GraphicsDevice.CreateSpriteFromFile(_T("ene_nin.png"), Color(255, 255, 255));
	player = GraphicsDevice.CreateSpriteFromFile(_T("nin2Left.png"), Color(255, 255, 255));
	kunai = GraphicsDevice.CreateSpriteFromFile(_T("kunai.png"), Color(255, 255, 255));
	kunai2 = GraphicsDevice.CreateSpriteFromFile(_T("kunai2.png"), Color(255, 255, 255));
	Space = GraphicsDevice.CreateSpriteFromFile(_T("攻撃(Space).png"));
	Right = GraphicsDevice.CreateSpriteFromFile(_T("移動(右).png"));
	Up = GraphicsDevice.CreateSpriteFromFile(_T("ジャンプ(上).png"));
	Title = GraphicsDevice.CreateSpriteFromFile(_T("タイトル画面（修正）.png"));
	hp = GraphicsDevice.CreateSpriteFromFile(_T("HPアイコン (1).png"));
	end = GraphicsDevice.CreateSpriteFromFile(_T("ゲームオーバー.png"));
	floor2 = GraphicsDevice.CreateSpriteFromFile(_T("5F.png"));
	clear = GraphicsDevice.CreateSpriteFromFile(_T("clear.png"));
	jump = GraphicsDevice.CreateSpriteFromFile(_T("nin_Jump.png"), Color(255, 255, 255));
	nin2 = GraphicsDevice.CreateSpriteFromFile(_T("nin2.png"), Color(255, 255, 255));
	nin2Left = GraphicsDevice.CreateSpriteFromFile(_T("nin2Left.png"), Color(255, 255, 255));
	ohiroma = GraphicsDevice.CreateSpriteFromFile(_T("大広間.png"));
	open = SoundDevice.CreateSoundFromFile(_T("open.wav"));
	close = SoundDevice.CreateSoundFromFile(_T("close.wav"));
	endtaiko = SoundDevice.CreateSoundFromFile(_T("clear.wav"));
	text = GraphicsDevice.CreateSpriteFont(_T("游明朝 Demibold"), 60);
	text2 = GraphicsDevice.CreateSpriteFont(_T("游明朝 Demibold"), 40);

	hp_count = 192.0f;

	if (game_scene == 1)
	{
       Initialize_1_3();
	}
		if (game_scene == 3)
	{
		Initialize_LastStage();
	}
	return true;
}



//1ステ
void GameMain::Initialize_1_3()
{ //1ステ
		

		chara_x = 0; chara_y = 530; time = 0; frame = 0;
		kunai_x = chara_x, kunai_y = chara_y; //攻撃用クナイの初期座標
		floor1_1x = 0;//背景のスクロール
		floor1_1y = 0; 
		player_state = 0, jump_state = 0; hit_enemy_state = 0; hit_enemy2_state = 0; jump_enemy_state = 0;
		jumpspeed = 0; jumptime = 0; zahyou = 0;  kunai_flag = false;
		enemy_jumpspeed = 0; enemy_jumptime = 0; enemy_zahyou = 0;
		enemyhit_count = 0;

		enemy_x =  400.0f;
		enemy_y = 530.0f;
		 enemy_x2 = 850.0f;
		enemy_y2 = 530.0f;

		speed = 1.0f;

		text = GraphicsDevice.CreateSpriteFont(_T("游明朝 Demibold"), 60);
		text2 = GraphicsDevice.CreateSpriteFont(_T("ＭＳ Ｐ明朝"), 40);

		enemy_move_flg = false;
		enemy_move_flg2 = false;
		//ここまで1ステ
	}


void GameMain::Initialize_LastStage()
{ //最終ステージ
	
	chara_x = 0; chara_y = 530;
	kunai_x = chara_x, kunai_y = chara_y; //攻撃用クナイの初期座標
	floor3_1x = 0;//背景のスクロール
	makimono_x = 750; makimono_y = 480;
	player_state = 0, jump_state = 0; player_frame = 0.0f;
	jumpspeed = 0; jumptime = 0; zahyou = 0; kunai_flag = false;
	ohiroma_flag = false;

	

	clear_flag = false;


	return;
}

//最終ステージ









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
	KeyboardState Key = Keyboard->GetState();
	KeyboardBuffer Key_buf = Keyboard->GetBuffer();
	if (game_scene == 0) {
		if (Key.IsKeyDown(Keys_Enter)) {
			game_scene = 1;
		}
	}

	if (game_scene == 1) {
		//敵往復移動
		if (enemy_move_flg == false)
		{
			enemy_x = enemy_x - speed;
			if (enemy_x < 300) { enemy_x = 300; enemy_move_flg = true; }

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
		if (hp_count = 0) {
			game_scene = 4;
		}




		//プレイヤー&&プレイヤー移動制限
		if (game_scene == 1) {
			MainPlayer_1_3();
		}
		//プレイヤー&&プレイヤー移動制限
		if (game_scene == 3) {
			MainPlayer_LastStage();
		}

	}
	return 0;
}

//1ステ
	void GameMain::MainPlayer_1_3()
	{   //1ステ

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

			jumptime = jumptime + 0.25;

			chara_y -= jumpspeed;

			chara_y = zahyou - (jumpspeed * jumptime - 0.5 * 9.80665 * jumptime * jumptime);

			if (chara_y > 530) {
				chara_y = 530;
				jump_state = 0;
			}
		}

		// 敵ジャンプ
		if (jump_enemy_state == 0) {
			if (Key_buf.IsPressed(Keys_Up)) {

				enemy_zahyou = enemy_y2;
				enemy_jumpspeed = 70;
				enemy_jumptime = 0;
				jump_enemy_state = 1;
			}
		}
		if (jump_enemy_state == 1) {
			if (Key.IsKeyDown(Keys_Up)) {
				if (enemy_jumpspeed >= 70) {
					enemy_jumpspeed = 70;
				}
			}

			enemy_jumptime = enemy_jumptime + 0.25;

			enemy_y2 -= enemy_jumpspeed;

			enemy_y2 = zahyou - (enemy_jumpspeed * enemy_jumptime - 0.5 * 9.80665 * enemy_jumptime * enemy_jumptime);

			if (enemy_y2 > 530) {
				enemy_y2 = 530;
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
		if (kunai_x > enemy_x + 100.0f - 20.0f || kunai_x + 8.0f < enemy_x ||
			kunai_y > enemy_y + 120.0f - 50.0f || kunai_y + 5.0f < enemy_y) {
			// 当たっていない
		}
		else {
			// 当たっている
			if (Key.IsKeyDown(Keys_Space)) {
				hit_enemy_state = 1;
			}
		}

		//敵　―　攻撃用クナイ
		if (kunai_x > enemy_x2 + 60.0f - 10.0f || kunai_x + 8.0f < enemy_x2 ||
			kunai_y > enemy_y2 + 110.0f - 10.0f || kunai_y + 5.0f < enemy_y2) {
			// 当たっていない
		}
		else {
			// 当たっている
			if (Key.IsKeyDown(Keys_Space)) {
				hit_enemy2_state = 1;
			}
		}
		if (hit_enemy_state == 0) {
			if (chara_x > enemy_x + 100.0f - 20.0f || chara_x + 80.0f - 30.0f < enemy_x ||
				chara_y > enemy_y + 120.0f - 50.0f || chara_y + 110.0f - 10.0f < enemy_y) {
				// 当たっていない
			}
			else {
				// 当たっている
				hp_count = hp_count - 62;
			}
		}

		if (hit_enemy2_state == 0) {
			if (chara_x > enemy_x2 + 60.0f - 10.0f || chara_x + 80.0f - 30.0f < enemy_x2 ||
				chara_y > enemy_y2 + 110.0f - 10.0f || chara_y + 110.0f - 10.0f < enemy_y2) {
				// 当たっていない
			}
			else {
				// 当たっている
				hp_count = hp_count - 62;
			}
		}
	}

//最終ステージ
	void GameMain::MainPlayer_LastStage()
	{   //最終ステージ

		KeyboardState Key = Keyboard->GetState();
		KeyboardBuffer Key_buf = Keyboard->GetBuffer();
		//移動

		if (clear_flag == true && Key_buf.IsPressed(Keys_Enter)) {
			game_scene = 0;
		}

		if (ohiroma_flag == false && Key.IsKeyDown(Keys_Right)) {
			player_state = 0;
			chara_x += 3.0f;
			floor3_1x -= 12.0f;
		}


		// ジャンプ
		if (ohiroma_flag == false) {
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


				//敵　―　プレイヤー当たり判定(敵を複数表示する予定。)
				if (hit_enemy_state == 0) {
					if (chara_x > enemy_x + 100.0f - 20.0f || chara_x + 80.0f - 30.0f < enemy_x ||
						chara_y > enemy_y + 120.0f - 50.0f || chara_y + 110.0f - 10.0f < enemy_y) {
						// 当たっていない
					}
					else {
						// 当たっている
						enemyhit_count = 1;
					}
				}

				if (hit_enemy2_state == 0) {
					if (chara_x > enemy_x2 + 60.0f - 10.0f || chara_x + 80.0f - 30.0f < enemy_x2 ||
						chara_y > enemy_y2 + 110.0f - 10.0f || chara_y + 110.0f - 10.0f < enemy_y2) {
						// 当たっていない
					}
					else {
						// 当たっている
						enemyhit_count = 1;
					}
				}

				//階段当たり判定
				if (chara_x > floor1_1x + 3440.0f || chara_x + 200.0f - 70.0f < floor1_1x + 2600 ||
					chara_y > floor1_1y + 550.0f || chara_y + 250.0f - 10.0f < floor1_1y) {

				}
				else {
					kunai_flag = false;
					chara_y = -1.4f * chara_x + 1600;
					if (chara_y < 100.0f) {
						//シーン遷移するプログラム
						game_scene = 2;

					}

					chara_y -= jumpspeed;

					chara_y = zahyou - (jumpspeed * jumptime - 0.5 * 9.80665 * jumptime * jumptime);

					if (chara_y > 530) {
						chara_y = 530;
						jump_state = 0;
					}
				}
			}

			//大広間突入
			if (chara_x == 1150) {
				close->Play();
				ohiroma_flag = true;
				chara_x = 0;
				chara_y = 550;
			}

			//背景移動制限
			if (ohiroma_flag == false) {
				if (chara_x < 0) {
					floor3_1x = 0;
				}
				if (floor3_1x < -2560) {
					floor3_1x = -2560;
				}
				if (floor3_1x > -5) {
					chara_x = 0;
				}


				if (chara_x < 0) {
					chara_x = 0;
				}
				if (chara_x > 1150) {
					chara_x = 1150;
					open->Play();

				}

				if (chara_x < 0) {
					chara_x = 0;
				}
				if (chara_x > 1150) {
					chara_x = 1150;
				}
			}
			//ここまで1ステ


		//大広間移動
			if (ohiroma_flag == true && clear_flag == false) {
				if (Key.IsKeyDown(Keys_Up)) {
					player_state = 0;
					chara_y -= 3.0f;
				}
				if (Key.IsKeyDown(Keys_Down)) {
					player_state = 0;
					chara_y += 3.0f;
				}

				if (Key.IsKeyDown(Keys_Right)) {
					player_state = 0;
					chara_x += 3.0f;
				}
				if (Key.IsKeyDown(Keys_Left)) {
					player_state = 1;
					chara_x -= 3.0f;
				}
			}

			//大広間移動制限
			if (ohiroma_flag == true && clear_flag == false) {
				if (chara_x < 0) { chara_x = 0; }
				if (chara_x > 1150) { chara_x = 1150; }
				if (chara_y < 400) { chara_y = 400; }
				if (chara_y > 580) { chara_y = 580; }

				//巻物ープレイヤーの当たり判定
				if (chara_x > makimono_x + 136.0f || chara_x + 128.0f - 80.0f < makimono_x ||
					chara_y > makimono_y + 184.0f || chara_y + 128.0f < makimono_y) {
					// 当たっていない
				}
				else {
					// 当たっている
					clear_flag = true;
				}

				if (clear_flag == true) {
					endtaiko->Play();
				}

			}
		}
	}
//ここまで最終ステージ






/// <summary>
/// This is called when the game should draw itself.
/// </summary>
void GameMain::Draw()
{
	// TODO: Add your drawing code here
	GraphicsDevice.Clear(Color_CornflowerBlue);

	GraphicsDevice.BeginScene();


	SpriteBatch.Begin();


	if (game_scene == 0) {
		SpriteBatch.Draw(*Title, Vector3(0, 0, 0));
	}

	if (game_scene == 1)
	{
	Draw_1_3();
    }

		if (game_scene == 3)
	{
		Draw_LastStage();
	}
		if (game_scene == 4) {
			SpriteBatch.Draw(*end, Vector3(0, 0, 0));
		}
	SpriteBatch.End();




	SpriteBatch.End();


	GraphicsDevice.EndScene();


}

//1ステ
void GameMain::Draw_1_3()
{  //1ステ
	
		if (jump_state == 0) { SpriteBatch.Draw(*player, Vector3(chara_x, chara_y, -1)); }
		if (jump_state == 1) { SpriteBatch.Draw(*jump, Vector3(chara_x, chara_y, -1)); }

		SpriteBatch.Draw(*hp, Vector3(0, 0, -1), RectWH(hp_count, 0, 62, 60));

		if (player_state == 0 && kunai_flag == true) { SpriteBatch.Draw(*kunai, Vector3(kunai_x, kunai_y, -1)); }

		SpriteBatch.Draw(*Right, Vector3(50, 100, -1));

		SpriteBatch.Draw(*Up, Vector3(50,175, -1));

		SpriteBatch.Draw(*floor, Vector3(floor3_1x, 0.0f, 0.0f));

		SpriteBatch.Draw(*Space, Vector3(50, 250, -1));

	GraphicsDevice.EndScene();

}

//最終ステージ
void GameMain::Draw_LastStage()
{  //最終ステージ

	if (player_state == 0 && jump_state == 0 && ohiroma_flag == false) { SpriteBatch.Draw(*nin2Left, Vector3(chara_x, chara_y, -1)); }

	if (jump_state == 1) { SpriteBatch.Draw(*jump, Vector3(chara_x, chara_y, -1)); }

	SpriteBatch.Draw(*hp, Vector3(0, 0, -1), RectWH(hp_count, 0, -62, 60));

	if (ohiroma_flag == false) { SpriteBatch.Draw(*Right, Vector3(50, 140, -1)); }
	if (ohiroma_flag == false) { SpriteBatch.Draw(*Up, Vector3(50, 250, -1)); }

	
	if (ohiroma_flag == true) { SpriteBatch.Draw(*ohiroma, Vector3(0, 0, 0)); }

	KeyboardState Key = Keyboard->GetState();

	if (ohiroma_flag == true && player_state == 0) { SpriteBatch.Draw(*nin2Left, Vector3(chara_x, chara_y, -1)); }
	if (ohiroma_flag == true && player_state == 1) { SpriteBatch.Draw(*nin2, Vector3(chara_x, chara_y, -1)); }


	SpriteBatch.DrawString(text, Vector2(100, 10), Color_White, _T("%.0f秒"), time);
	if (clear_flag == true) { SpriteBatch.DrawString(text2, Vector2(200, 600), Color_White, _T("タイトルに戻るためEnterキーを押す")); }
	if (clear_flag == true) { SpriteBatch.Draw(*clear, Vector3(250, 100, 0)); }

	SpriteBatch.Draw(*floor2, Vector3(floor1_1x, 0.0f, 0.0f));

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
		SpriteBatch.Draw(*ene_nin, Vector3(enemy_x2, enemy_y2, -1.0f));
	}
	if (enemy_move_flg2 == true && hit_enemy2_state == 0)
	{
		SpriteBatch.Draw(*ene_nin, Vector3(enemy_x2, enemy_y2, -1.0f));
	}

	//敵とプレイヤーが当たった時の処理
	if (enemyhit_count == 1) {

		enemyhit_count = 0;
	}
}




