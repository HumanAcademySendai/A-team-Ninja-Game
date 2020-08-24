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
	
	if (game_scene == 3)
	{
		Initialize_LastStage();
	}




	/*Game_scene_flg2 = false;*/
	return true;
}

//最終ステージ
void GameMain::Initialize_LastStage()
{ //最終ステージ
	floor = GraphicsDevice.CreateSpriteFromFile(_T("5F.png"));
	clear = GraphicsDevice.CreateSpriteFromFile(_T("clear.png"));
	jump = GraphicsDevice.CreateSpriteFromFile(_T("nin_Jump.png"),Color(255,255,255));
	nin2 = GraphicsDevice.CreateSpriteFromFile(_T("nin2.png"),Color(255,255,255));
	nin2Left = GraphicsDevice.CreateSpriteFromFile(_T("nin2Left.png"),Color(255,255,255));
	Right = GraphicsDevice.CreateSpriteFromFile(_T("移動(右).png"));
	Up = GraphicsDevice.CreateSpriteFromFile(_T("ジャンプ(上).png"));
	ohiroma = GraphicsDevice.CreateSpriteFromFile(_T("大広間.png"));
	open = SoundDevice.CreateSoundFromFile(_T("open.wav"));
	close = SoundDevice .CreateSoundFromFile(_T("close.wav"));
	endtaiko = SoundDevice.CreateSoundFromFile(_T("clear.wav"));
	chara_x = 0; chara_y = 530;
	time = 0; frame = 0; //前のタイムを引き継ぐ
	kunai_x = chara_x, kunai_y = chara_y; //攻撃用クナイの初期座標
	floor3_1x = 0;//背景のスクロール
	makimono_x = 750; makimono_y = 480;
	player_state = 0, jump_state = 0; player_frame = 0.0f;
	jumpspeed = 0; jumptime = 0; zahyou = 0; kunai_flag = false;
	ohiroma_flag = false;

	text = GraphicsDevice.CreateSpriteFont(_T("游明朝 Demibold"), 60);
	text2 = GraphicsDevice.CreateSpriteFont(_T("游明朝 Demibold"), 30);

	clear_flag = false;

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

	//プレイヤー&&プレイヤー移動制限
	if (game_scene == 3) {
		MainPlayer_LastStage();
	}

	return 0;
}
//最終ステージ
void GameMain::MainPlayer_LastStage()
{   //最終ステージ

	KeyboardState Key = Keyboard->GetState();
	KeyboardBuffer Key_buf = Keyboard->GetBuffer();
	//移動


	
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

			chara_y -= jumpspeed;

			chara_y = zahyou - (jumpspeed * jumptime - 0.5 * 9.80665 * jumptime * jumptime);

			if (chara_y > 530) {
				chara_y = 530;
				jump_state = 0;
			}
		}
	}

	//タイム(カウントアップ)
	if (clear_flag == false && time < 10000) {
		frame += 1;
		if (frame >= 60) {
			time += 1;
			frame = 0;
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
	}

	//大広間移動
	if (ohiroma_flag == true && clear_flag == false) {
		if (Key.IsKeyDown(Keys_Up)) {
			player_state = 0;
			chara_y -= 4.0f;
		}
		if (Key.IsKeyDown(Keys_Down)) {
			player_state = 0;
			chara_y += 4.0f;
		}

		if (Key.IsKeyDown(Keys_Right)) {
			player_state = 0;
			chara_x += 4.0f;
		}
		if (Key.IsKeyDown(Keys_Left)) {
			player_state = 1;
			chara_x -= 4.0f;
		}
	}

	//大広間移動制限
	if (ohiroma_flag == true && clear_flag == false) {
		if (chara_x < 0) { chara_x = 0; }
		if (chara_x > 1150) { chara_x = 1150; }
		if (chara_y < 400) { chara_y = 400; }
		if (chara_y > 580) { chara_y = 580; }

		//巻物ープレイヤーの当たり判定
		if (chara_x > makimono_x + 136.0f  || chara_x + 128.0f - 80.0f < makimono_x ||
			chara_y > makimono_y + 184.0f  || chara_y + 128.0f         < makimono_y) {
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
	if (game_scene == 3)
	{
		Draw_LastStage();
	}

	SpriteBatch.End();


	GraphicsDevice.EndScene();

}

//最終ステージ
void GameMain::Draw_LastStage()
{  //最終ステージ

	if (player_state == 0 && jump_state == 0 && ohiroma_flag == false) { SpriteBatch.Draw(*nin2Left, Vector3(chara_x, chara_y, -1)); }

	if (jump_state == 1) { SpriteBatch.Draw(*jump, Vector3(chara_x, chara_y, -1)); }


	if (ohiroma_flag == false) { SpriteBatch.Draw(*Right, Vector3(50, 140, -1)); }
	if (ohiroma_flag == false) {SpriteBatch.Draw(*Up, Vector3(50, 250, -1));}

	SpriteBatch.Draw(*floor, Vector3(floor3_1x, 0.0f, 0.0f));
	if (ohiroma_flag == true) { SpriteBatch.Draw(*ohiroma, Vector3(0, 0, 0)); }

	KeyboardState Key = Keyboard->GetState();

	if (ohiroma_flag == true && player_state == 0) { SpriteBatch.Draw(*nin2Left, Vector3(chara_x, chara_y, -1)); }
	if (ohiroma_flag == true && player_state == 1) { SpriteBatch.Draw(*nin2, Vector3(chara_x, chara_y, -1)); }

	SpriteBatch.DrawString(text, Vector2(100, 10), Color_White, _T("%.0f秒"), time);
	if (clear_flag == true) { SpriteBatch.Draw(*clear, Vector3(250, 100, 0)); }


	//ここまで最終ステージ
}