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
	//1��3�X�e
	Initialize_1_3();
	//�Q�ƂS



	return true;
}

//1��3�X�e
void GameMain::Initialize_1_3()
{ //1��3�X�e
	game_scene = 1;
	if (game_scene == 1) {
		floor = GraphicsDevice.CreateSpriteFromFile(_T("1,3F.png"));
		enemy = GraphicsDevice.CreateSpriteFromFile(_T("samurai.png"));
		player = GraphicsDevice.CreateSpriteFromFile(_T("nin.png"), Color(255, 255, 255));
		leftplayer = GraphicsDevice.CreateSpriteFromFile(_T("nin2.png"), Color(255, 255, 255));
		kunai = GraphicsDevice.CreateSpriteFromFile(_T("kunai.png"), Color(255, 255, 255));
		kunai2 = GraphicsDevice.CreateSpriteFromFile(_T("kunai2.png"), Color(255, 255, 255));

		chara_x = 0; chara_y = 550; time = 0; frame = 0;
		kunai_x = chara_x, kunai_y = chara_y; //�U���p�N�i�C�̏������W
		kunai2_x = chara_x, kunai2_y = chara_y;
		floor1_1x = 0;//�w�i�̃X�N���[��
		floor1_1y = 0; kaidan1_x = 1000; kaidan1_y = 0;
		player_state = 0, jump_state = 0; hit_state = 0; shot_count = 0;
		jumpspeed = 0; jumptime = 0; zahyou = 0; kunai_flag = false;

		enemy_x = 1100.0f;
		enemy_y = 530.0f;
		speed = 2.0f;

		text = GraphicsDevice.CreateSpriteFont(_T("������ Demibold"), 60);

		enemy_move_flg = false;
		//�����܂�1��3�X�e
	}
}


//2��4�X�e
void GameMain::Initialize_2_4()
{//2��4�X�e
	if (game_scene == 2) {
		floor = GraphicsDevice.CreateSpriteFromFile(_T("floor.png"));
		kaidan = GraphicsDevice.CreateSpriteFromFile(_T("kaidan2.png"));
		enemy = GraphicsDevice.CreateSpriteFromFile(_T("samurai.png"));
		player = GraphicsDevice.CreateSpriteFromFile(_T("nin.png"), Color(255, 255, 255));
		leftplayer = GraphicsDevice.CreateSpriteFromFile(_T("nin2.png"), Color(255, 255, 255));
		kunai = GraphicsDevice.CreateSpriteFromFile(_T("kunai.png"), Color(255, 255, 255));
		kunai2 = GraphicsDevice.CreateSpriteFromFile(_T("kunai2.png"), Color(255, 255, 255));

		chara_x = 1100; chara_y = 550;
		kunai_x = chara_x, kunai_y = chara_y; //�U���p�N�i�C�̏������W
		kunai2_x = chara_x, kunai2_y = chara_y;
		floor2_0x = 1280.0f; floor2_1x = 0; floor2_2x = -1280.0f; kaidan2_x = -1280.0f * 2;//�w�i�̃X�N���[��

		player_state = 1, jump_state = 0; hit_state = 0; shot_count = 0;
		jumpspeed = 0; jumptime = 0; zahyou = 0; kunai_flag = false;

		enemy_x = 1100.0f;
		enemy_y = 530.0f;
		speed = 2.0f;
		enemy_move_flg = false;
		//�����܂�2��4�X�e
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
	//�G�����ړ�
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
	//�v���C���[&&�v���C���[�ړ�����
	{
		MainPlayer_1_3();
	}

	return 0;
}
//1��3�X�e
void GameMain::MainPlayer_1_3()
{   //1��3�X�e
	if (game_scene == 1) {
		KeyboardState Key = Keyboard->GetState();
		KeyboardBuffer Key_buf = Keyboard->GetBuffer();
		//�ړ�
		if (floor1_1x < 2300) {
			if (Key.IsKeyDown(Keys_Left)) {
				player_state = 1;
				chara_x -= 6.0f;
				floor1_1x += 12.0f;
			}
		}
		if (Key.IsKeyDown(Keys_Right)) {
			player_state = 0;
			chara_x += 6.0f;
			floor1_1x -= 12.0f;

		}

		// �W�����v
		if (jump_state == 0) {
			if (Key_buf.IsPressed(Keys_Up)) {

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
			floor1_1x = 0;
		}
		if (floor1_1x < -1280) {
			floor1_1x = -1280;
		}
		if (floor1_1x > -5) {
			chara_x = 0;
		}
		if (chara_y > 550) {
			chara_y = 550;
		}
		//����(�U���p�N�i�C)
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
		//�U���p�N�i�C���W
		kunai_x = chara_x + 80, kunai_y = chara_y + 50;
		kunai2_x = chara_x - 10, kunai2_y = chara_y + 50;
		//�G�@�\�@�U���p�N�i�C
		if (kunai_x > enemy_x + 52.0f || kunai_x + 8.0f < enemy_x ||
			kunai_y > enemy_y + 73.0f || kunai_y + 5.0f < enemy_y) {
			// �������Ă��Ȃ�
		}
		else {
			// �������Ă���
			if (Key.IsKeyDown(Keys_Space)) {
				hit_state = 1;
			}
		}
		if (kunai2_x > enemy_x + 52.0f || kunai2_x + 8.0f < enemy_x ||
			kunai2_y > enemy_y + 73.0f || kunai2_y + 5.0f < enemy_y) {
			// �������Ă��Ȃ�
		}
		else {
			// �������Ă���
			if (Key.IsKeyDown(Keys_Space)) {
				hit_state = 1;
			}

		}
		//�G�@�\�@�v���C���[�����蔻��(�G�𕡐��\������\��B)(���̎���for�ŏ���������)
		if (hit_state == 0) {
			if (chara_x > enemy_x + 70.0f - 30.0f || chara_x + 96.0f - 30.0f < enemy_x ||
				chara_y > enemy_y + 130.0f - 21.0f || chara_y + 100.0f - 30.0f < enemy_y) {
				// �������Ă��Ȃ�
			}
			else {
				// �������Ă���

			}
		}

		//�K�i�����蔻��
		if (chara_x > floor1_1x + 2300.0f || chara_x + 96.0f - 30.0f < floor1_1x ||
			chara_y > floor1_1y + 550.0f || chara_y + 100.0f - 30.0f < floor1_1y) {

		}
		else {
			chara_y = -1.4f * chara_x + 1500;
			if (chara_y < 100.0f) {
				game_scene = 2;
			}
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
	}
		//�����܂�1��3�X�e
	
}

//2��4�X�e
void GameMain::MainPlayer_2_4()
{//2��4�X�e
	if (game_scene == 2) {
		KeyboardState Key = Keyboard->GetState();
		KeyboardBuffer Key_buf = Keyboard->GetBuffer();
		//�ړ�
		if (Key.IsKeyDown(Keys_A)) {
			player_state = 1;
			chara_x -= 6.0f;
			floor2_0x += 6.0f;
			floor2_1x += 6.0f;
			floor2_2x += 6.0f;
			kaidan2_x += 6.0f;
		}
		if (Key.IsKeyDown(Keys_D)) {
			player_state = 0;
			chara_x += 6.0f;
			floor2_0x -= 6.0f;
			floor2_1x -= 6.0f;
			floor2_2x -= 6.0f;
			kaidan2_x -= 6.0f;

		}
		//�w�i�ړ�����
		if (kaidan2_x < -1280 * 2) {
			floor2_0x = 1280.0f; floor2_1x = 0.0f; floor2_2x = -1280.0f;  kaidan2_x = -1280 * 2;
		}
		if (kaidan2_x > 0) {
			floor2_0x = 1280 * 3;	floor2_1x = 1280 * 2; floor2_2x = 1280; kaidan2_x = 0.0f;
		}
		//����(�U���p�N�i�C)
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
		//�U���p�N�i�C���W
		kunai_x = chara_x + 80, kunai_y = chara_y + 50;
		kunai2_x = chara_x - 10, kunai2_y = chara_y + 50;
		if (chara_x < 0) {
			chara_x = 0;
		}
		if (chara_x > 1150) {
			chara_x = 1150;
		}
		if (chara_y > 550) {
			chara_y = 550;
		}
		//�G�@�\�@�U���p�N�i�C
		if (kunai_x > enemy_x + 52.0f || kunai_x + 8.0f < enemy_x ||
			kunai_y > enemy_y + 73.0f || kunai_y + 5.0f < enemy_y) {
			// �������Ă��Ȃ�
		}
		else {
			// �������Ă���
			if (Key.IsKeyDown(Keys_Z)) {
				hit_state = 1;
			}
		}
		if (kunai2_x > enemy_x + 52.0f || kunai2_x + 8.0f < enemy_x ||
			kunai2_y > enemy_y + 73.0f || kunai2_y + 5.0f < enemy_y) {
			// �������Ă��Ȃ�
		}
		else {
			// �������Ă���
			if (Key.IsKeyDown(Keys_Z)) {
				hit_state = 1;
			}

		}
		//�G�@�\�@�v���C���[�����蔻��(�G�𕡐��\������\��B)(���̎���for�ŏ���������)
		if (hit_state == 0) {
			if (chara_x > enemy_x + 70.0f - 30.0f || chara_x + 96.0f - 30.0f < enemy_x ||
				chara_y > enemy_y + 130.0f - 21.0f || chara_y + 100.0f - 30.0f < enemy_y) {
				// �������Ă��Ȃ�
			}
			else {
				// �������Ă���

			}
		}
		// �W�����v
		if (jump_state == 0) {
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
		}
		//�����܂�2��4�X�e
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

	Draw_1_3();


	SpriteBatch.End();


	GraphicsDevice.EndScene();

	//Canvas canvas = GraphicsDevice.LockCanvas();

	//Paint paint;
	//paint.SetPaintColor(Color_Yellow);
	//canvas.DrawRect(Rect(floor1_1x + 2100,floor1_1y + 0,floor1_1x + 2560,floor1_1y - 700), paint);


	//GraphicsDevice.UnlockCanvas();
}

//1��3�X�e
void GameMain::Draw_1_3()
{  //1��3�X�e
	if (game_scene == 1) {
		if (player_state == 0) { SpriteBatch.Draw(*player, Vector3(chara_x, chara_y, -1)); }
		if (player_state == 1) { SpriteBatch.Draw(*leftplayer, Vector3(chara_x, chara_y, -1)); }
		for (int i = 0; i < SHOT_MAX; i++)
		{
			if (shot_flg[i] == 1 && player_state == 0) { SpriteBatch.Draw(*kunai, Vector3(shot_x[i], shot_y[i], -1)); }
			if (shot_flg[i] == 1 && player_state == 1) { SpriteBatch.Draw(*kunai2, Vector3(shot_x[i], shot_y[i], -1)); }
		}
		if (player_state == 0 && kunai_flag == true) { SpriteBatch.Draw(*kunai, Vector3(kunai_x, kunai_y, -1)); }
		if (player_state == 1 && kunai_flag == true) { SpriteBatch.Draw(*kunai2, Vector3(kunai2_x, kunai2_y, -1)); }

		SpriteBatch.Draw(*floor, Vector3(floor1_1x, 0.0f, 0.0f));

		SpriteBatch.DrawString(text, Vector2(100, 10), Color_Black, _T("%.0f�b"), time);

		if (enemy_move_flg == false && hit_state == 0)
		{
			SpriteBatch.Draw(*enemy, Vector3(enemy_x, enemy_y, -1.0f));
		}
		if (enemy_move_flg == true && hit_state == 0)
		{
			SpriteBatch.Draw(*enemy, Vector3(enemy_x, enemy_y, -1.0f));
		}
		//�����܂�1��3�X�e
	}
}
//2��4�X�e
void GameMain::Draw_2_4()
{//2��4�X�e
	if (game_scene == 2) {
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
		SpriteBatch.Draw(*kaidan, Vector3(kaidan2_x, 0.0f, 0.0f));

		SpriteBatch.DrawString(text, Vector2(100, 10), Color_Black, _T("%.0f�b"), time);

		if (enemy_move_flg == false && hit_state == 0)
		{
			SpriteBatch.Draw(*enemy, Vector3(enemy_x, enemy_y, -1.0f));
		}
		if (enemy_move_flg == true && hit_state == 0)
		{
			SpriteBatch.Draw(*enemy, Vector3(enemy_x, enemy_y, -1.0f));
		}
		//�����܂�2��4�X�e
	}
}
