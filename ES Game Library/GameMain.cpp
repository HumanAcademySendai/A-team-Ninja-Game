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
	/*player = GraphicsDevice.CreateAnimationModelFromFile(_T("nin3_walk.0001.png"));
	leftplayer = GraphicsDevice.CreateAnimationModelFromFile(_T("nin3_walk.0001.png"));*/
	kunai = GraphicsDevice.CreateSpriteFromFile(_T("kunai.png"), Color(255, 255, 255));
	/*player_jump = GraphicsDevice.CreateModelFromFile(_T("nin_Jump.png"));*/
	player = GraphicsDevice.CreateSpriteFromFile(_T("image1 (1) (1).png"));

	/*player->SetScale(1, -1, 1);
	chara_x = 0; chara_y = 514;
	player->SetPosition(chara_x, chara_y, 0);
	leftplayer->SetScale(1, -1, 1);
	leftplayer->SetPosition(chara2_x, chara2_y, 0);
	leftplayer->SetRotation(90, 0, 0);*/

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
	floor3_0x = -1280.0f; floor3_1x = 0; floor3_2x = 1280.0f; kaidan3_x = 1280.0f * 2;//背景のスクロール
	floor1_0x = -1280.0f; floor1_1x = 0; floor1_2x = 1280.0f; kaidan1_x = 1280.0f * 2;//背景のスクロール

	player_state = 0, jump_state = 0; hit_state = 0; shot_count = 0;
	jumpspeed = 0; jumptime = 0; zahyou = 0; kunai_flag = false;
	text = GraphicsDevice.CreateSpriteFont(_T("游明朝 Demibold"), 60);

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

	//1と3


	Game_scene_flg = false;

	if (Game_scene_flg = true)

	{
       Initialize_1_3();
	}
	
	    
	//２と４

	
	WindowTitle(_T("忍者　飛影"));
	game_scene = 3;
	if (game_scene == 3)
	{
		Initialize_LastStage();
	}




	/*Game_scene_flg2 = false;*/

	game_scene == 0;

	return true;
}


void GameMain::steage2()
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
	if (chara_y > 550) {
		chara_y = 550;
	}
	//プレイヤー
	{
		MainPlayer();
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
		floor3_0x += 6.0f;
		floor3_1x += 6.0f;
		floor3_2x += 6.0f;
		kaidan3_x += 6.0f;
	}
	if (Key.IsKeyDown(Keys_Left)) {
		player_state = 0;
		chara_x += 6.0f;
		floor2_0x -= 6.0f;
		floor2_1x -= 6.0f;
		floor2_2x -= 6.0f;
		kaidan2_x -= 6.0f;

		floor3_0x -= 6.0f;
		floor3_1x -= 6.0f;
		floor3_2x -= 6.0f;
		kaidan3_x -= 6.0f;
	}
	//背景移動制限
	if (kaidan2_x < -1280 * 2) {
		floor2_0x = 1280.0f; floor2_1x = 0.0f; floor2_2x = -1280.0f;  kaidan2_x = -1280 * 2;
	}
	if (kaidan2_x > 0) {
		floor2_0x = 1280 * 3;	floor2_1x = 1280 * 2; floor2_2x = 1280; kaidan2_x = 0.0f;
	}

	//背景移動制限
	if (chara_x < 0) {
		floor3_0x = -1280;	floor3_1x = 0; floor3_2x = 1280; kaidan3_x = 2560;
	}
	if (kaidan3_x < 0) {
		floor3_0x = -1280.0f * 3; floor3_1x = -1280.0f * 2; floor3_2x = -1280.0f;  kaidan3_x = 0;
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
	/*if (player_jump_flg == false) {
		player_jump->Rotation(90, 0, 0);
		if (Key.IsKeyDown(Keys_Left)) {
			player_jump_flg = true;
		}
	}
	if (player_jump_flg == true) {
		if (Key.IsKeyDown(Keys_Right)) {
			player_jump_flg = false;
		}
	}*/


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

//1と3ステ
void GameMain::Initialize_1_3()
{ //1と3ステ
		floor = GraphicsDevice.CreateSpriteFromFile(_T("1,3F.png"));
		enemy = GraphicsDevice.CreateSpriteFromFile(_T("samurai.png"));
		/*player = GraphicsDevice.CreateAnimationModelFromFile(_T("nin3_walk.0001.png"));
		leftplayer = GraphicsDevice.CreateAnimationModelFromFile(_T("nin3_walk.0001.png"));*/
		kunai = GraphicsDevice.CreateSpriteFromFile(_T("kunai.png"), Color(255, 255, 255));
		kunai2 = GraphicsDevice.CreateSpriteFromFile(_T("kunai2.png"), Color(255, 255, 255));

		chara_x = 0; chara_y = 550; time = 0; frame = 0;
		kunai_x = chara_x, kunai_y = chara_y; //攻撃用クナイの初期座標
		kunai2_x = chara_x, kunai2_y = chara_y;
		floor1_1x = 0;//背景のスクロール
		floor1_1y = 0; kaidan1_x = 1000;
		player_state = 0, jump_state = 0; hit_state = 0; shot_count = 0;
		jumpspeed = 0; jumptime = 0; zahyou = 0; kunai_flag = false;

		enemy_x = 1100.0f;
		enemy_y = 530.0f;
		speed = 2.0f;

		text = GraphicsDevice.CreateSpriteFont(_T("游明朝 Demibold"), 60);

		enemy_move_flg = false;
		//ここまで1と3ステ
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
	kunai_x = chara_x, kunai_y = chara_y; //攻撃用クナイの初期座標
	floor3_1x = 0;//背景のスクロール
	makimono_x = 750; makimono_y = 480;
	player_state = 0, jump_state = 0; player_frame = 0.0f;
	jumpspeed = 0; jumptime = 0; zahyou = 0; kunai_flag = false;
	ohiroma_flag = false;

	text2 = GraphicsDevice.CreateSpriteFont(_T("游明朝 Demibold"), 40);

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


	if (chara_x < 0) {
		chara_x = 0;
	}
	if (chara_x > 1150) {
		chara_x = 1150;
	}
	if (chara_y > 550) {
		chara_y = 550;
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

	//プレイヤー&&プレイヤー移動制限
	if (game_scene == 3) {
		MainPlayer_LastStage();
	}

	return ;
}
//最終ステージ
void GameMain::MainPlayer_LastStage()
{   //最終ステージ

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

		if (clear_flag == true && Key_buf.IsPressed(Keys_Enter)) {
			game_scene = 0;
		}
		if (Key.IsKeyDown(Keys_Left)) {

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
						jumpspeed = 80;
						jumpspeed = 60;
						jumptime = 0;
						jump_state = 1;
					}
				}
				if (jump_state == 1) {
					if (Key.IsKeyDown(Keys_Up)) {
						if (jumpspeed >= 80) {
							jumpspeed = 80;
						}
					}
					//jumpspeed -= 2;

					if (jumpspeed >= 60) {
						jumpspeed = 60;
					}
				}

				jumptime = jumptime + 0.25;

				chara_y -= jumpspeed;

				chara_y = zahyou - (jumpspeed * jumptime - 0.5 * 9.80665 * jumptime * jumptime);

				if (chara_y > 550) {
					chara_y = 550;
					jump_state = 0;
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
			if (floor1_1x < -1280) {
				floor1_1x = -1280;
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

			//階段当たり判定
			if (chara_x > floor1_1x + 2560.0f || chara_x + 96.0f - 30.0f < floor1_1x + 2100 ||
				chara_y > floor1_1y + 550.0f || chara_y + 100.0f - 30.0f < floor1_1y) {

			}
			else {
				chara_y = -1.4f * chara_x + 1500;
				if (chara_y < 100.0f) {
					Game_scene_flg = false;

				}
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
			/*if (player_jump_flg == false) {
				player_jump->Rotation(90, 0, 0);
				if (Key.IsKeyDown(Keys_Left)) {
					player_jump_flg = true;
				}
			}
			if (player_jump_flg == true) {
				if (Key.IsKeyDown(Keys_Right)) {
					player_jump_flg = false;
				}
			}*/
			//ここまで1と3ステ
			if (chara_y > 530) {
				chara_y = 530;
				jump_state = 0;
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
					if (jump_state == 1) {
						zahyou = chara_y;
						jumpspeed += 0.1;
						jump_state = 1;
						if (jumpspeed >= 25) {
							jumpspeed = 25;
							jump_state = 1;
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
		}
	}
}

void GameMain::scene_change()
{
	KeyboardState Key = Keyboard->GetState();
	KeyboardBuffer Key_buf = Keyboard->GetBuffer();

	if (game_scene == 0) {
		if (Key.IsKeyDown(Keys_Enter)) {
			game_scene = 1;
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
	/*if (game_scene == 1) {
		player->SetPosition(chara_x, chara_y, 0);
		player->Draw();
		player->AdvanceTime(GameTimer.GetElapsedSecond());
		GraphicsDevice.SetCamera(camera);
	}*/

	SpriteBatch.Begin();
	if (game_scene == 1) {
		SpriteBatch.Draw(*player, Vector3(chara_x, chara_y, 0.0f), RectWH(0, 0, 258, 254));
	}
	if (Game_scene_flg == true)
	{
	Draw_1_3();
    }
	
	if (game_scene == 3)
	{
		Draw_LastStage();
	}
	SpriteBatch.DrawString(text, Vector2(100, 10), Color_Black, _T("%.0f秒"), time);
	SpriteBatch.DrawString(text, Vector2(100, 10), Color_White, _T("%.0f秒"), time);

	SpriteBatch.End();


	GraphicsDevice.EndScene();

	//Canvas canvas = GraphicsDevice.LockCanvas();

	//Paint paint;
	//paint.SetPaintColor(Color_Yellow);
	//canvas.DrawRect(Rect(floor1_1x + 2300,floor1_1y + 0,floor1_1x + 2560,floor1_1y + 500), paint);


	//GraphicsDevice.UnlockCanvas();
}

//1と3ステ
void GameMain::Draw_1_3()
{  //1と3ステ

	for (int i = 0; i < SHOT_MAX; i++)
	{
		if (shot_flg[i] == 1 && player_state == 0) { SpriteBatch.Draw(*kunai, Vector3(shot_x[i], shot_y[i], -1)); }
		if (shot_flg[i] == 1 && player_state == 1) { SpriteBatch.Draw(*kunai2, Vector3(shot_x[i], shot_y[i], -1)); }
	}
	if (player_state == 0 && kunai_flag == true) { SpriteBatch.Draw(*kunai, Vector3(kunai_x, kunai_y, -1)); }
	if (player_state == 1 && kunai_flag == true) { SpriteBatch.Draw(*kunai2, Vector3(kunai2_x, kunai2_y, -1)); }
	if (game_scene == 1) {

		/*	if (player_state == 1) { SpriteBatch.Draw(*leftplayer, Vector3(chara_x, chara_y, -1)); }*/

		SpriteBatch.Draw(*hp1, Vector3(hp_x, 0, 0), RectWH(0, 0, hp_count, 60));
	}
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

	if (clear_flag == true) { SpriteBatch.DrawString(text2, Vector2(200, 600), Color_White, _T("タイトルに戻るためEnterキーを押す")); }
	if (clear_flag == true) { SpriteBatch.Draw(*clear, Vector3(250, 100, 0)); }
		if (player_state == 0 && kunai_flag == true) { SpriteBatch.Draw(*kunai, Vector3(kunai_x, kunai_y, -1)); }
		if (player_state == 1 && kunai_flag == true) { SpriteBatch.Draw(*kunai2, Vector3(kunai2_x, kunai2_y, -1)); }

	SpriteBatch.Draw(*floor, Vector3(floor3_0x, 0.0f, 0.0f));
	SpriteBatch.Draw(*floor, Vector3(floor3_1x, 0.0f, 0.0f));
	SpriteBatch.Draw(*floor, Vector3(floor3_2x, 0.0f, 0.0f));
	SpriteBatch.Draw(*kaidan, Vector3(kaidan3_x, 0.0f, 0.0f));

		if (enemy_move_flg == false && hit_state == 0)
		{
			SpriteBatch.Draw(*enemy, Vector3(enemy_x, enemy_y, -1.0f));
		}
		if (enemy_move_flg == true && hit_state == 0)
		{
			SpriteBatch.Draw(*enemy, Vector3(enemy_x, enemy_y, -1.0f));
		}
	if (game_scene == 0) {
		SpriteBatch.Draw(*Title, Vector3(0, 0, 0));
	}
	if (game_scene == 2) {
		SpriteBatch.Draw(*GameOver, Vector3(0, 0, 0));
	}
	if (game_scene == 3) {
		SpriteBatch.Draw(*Last, Vector3(0, 0, 0));
	}

	SpriteBatch.End();


	GraphicsDevice.EndScene();



}