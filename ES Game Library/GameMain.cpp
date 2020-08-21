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
	//1��3


	Game_scene_flg = false;

	if (Game_scene_flg = true)
	{
		Initialize_LastStage();
	}




	/*Game_scene_flg2 = false;*/
	return true;
}

//1��3�X�e
void GameMain::Initialize_LastStage()
{ //1��3�X�e
	floor = GraphicsDevice.CreateSpriteFromFile(_T("5F.png"));
	player = GraphicsDevice.CreateSpriteFromFile(_T("nin.png"), Color(255, 255, 255));

	chara_x = 0; chara_y = 400; time = 0; frame = 0; //�O�̃^�C���������p��
	kunai_x = chara_x, kunai_y = chara_y; //�U���p�N�i�C�̏������W
	floor3_1x = 0;//�w�i�̃X�N���[��
	player_state = 0, jump_state = 0; 
	jumpspeed = 0; jumptime = 0; zahyou = 0; kunai_flag = false;

	speed = 0.5f;

	text = GraphicsDevice.CreateSpriteFont(_T("������ Demibold"), 60);

	enemy_move_flg = false;
	enemy_move_flg2 = false;
	//�����܂�1��3�X�e
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

	//�v���C���[&&�v���C���[�ړ�����

	MainPlayer_LastStage();


	return 0;
}
//1��3�X�e
void GameMain::MainPlayer_LastStage()
{   //1��3�X�e

	KeyboardState Key = Keyboard->GetState();
	KeyboardBuffer Key_buf = Keyboard->GetBuffer();
	//�ړ�



	if (Key.IsKeyDown(Keys_Right)) {
		player_state = 0;
		chara_x += 3.0f;
		floor3_1x -= 12.0f;

	}

	// �W�����v
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
		jumptime = jumptime + 0.15;

		chara_y -= jumpspeed;

		chara_y = zahyou - (jumpspeed * jumptime - 0.5 * 9.80665 * jumptime * jumptime);

		if (chara_y > 400) {
			chara_y = 400;
			jump_state = 0;
		}
	}

	//�^�C��(�J�E���g�A�b�v)
	if (time < 10000) {
		frame += 1;
		if (frame >= 60) {
			time += 1;
			frame = 0;
		}
	}

	//�w�i�ړ�����
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
	if (chara_x > 1000) {
		chara_x = 1000;
	}
}
//�����܂�1��3�X�e





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
		Draw_LastStage();
	}

	SpriteBatch.End();


	GraphicsDevice.EndScene();

	//Canvas canvas = GraphicsDevice.LockCanvas();

	//Paint paint;
	//paint.SetPaintColor(Color_Yellow);
	//canvas.DrawRect(Rect(floor1_1x + 2300,floor1_1y + 0,floor1_1x + 2560,floor1_1y + 500), paint);


	//GraphicsDevice.UnlockCanvas();
}

//1��3�X�e
void GameMain::Draw_LastStage()
{  //1��3�X�e

	if (player_state == 0) { SpriteBatch.Draw(*player, Vector3(chara_x, chara_y, -1)); }
	if (player_state == 1) { SpriteBatch.Draw(*leftplayer, Vector3(chara_x, chara_y, -1)); }

	if (player_state == 0 && kunai_flag == true) { SpriteBatch.Draw(*kunai, Vector3(kunai_x, kunai_y, -1)); }


	SpriteBatch.Draw(*floor, Vector3(floor3_1x, 0.0f, 0.0f));

	SpriteBatch.DrawString(text, Vector2(100, 10), Color_White, _T("%.0f�b"), time);


	//�����܂�1��3�X�e
}