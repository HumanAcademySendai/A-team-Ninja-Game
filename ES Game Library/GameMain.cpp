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
	WindowTitle(_T("�E�ҁ@��e"));

	//1�X�e
	game_scene = 0;

	floor = GraphicsDevice.CreateSpriteFromFile(_T("1,3F.png"));
	enemy = GraphicsDevice.CreateSpriteFromFile(_T("samurai.png"), Color(255, 255, 255));
	ene_nin = GraphicsDevice.CreateSpriteFromFile(_T("ene_nin.png"), Color(255, 255, 255));
	player = GraphicsDevice.CreateSpriteFromFile(_T("nin2Left.png"), Color(255, 255, 255));
	kunai = GraphicsDevice.CreateSpriteFromFile(_T("kunai.png"), Color(255, 255, 255));
	kunai2 = GraphicsDevice.CreateSpriteFromFile(_T("kunai2.png"), Color(255, 255, 255));
	Space = GraphicsDevice.CreateSpriteFromFile(_T("�U��(Space).png"));
	Right = GraphicsDevice.CreateSpriteFromFile(_T("�ړ�(�E).png"));
	Up = GraphicsDevice.CreateSpriteFromFile(_T("�W�����v(��).png"));
	Title = GraphicsDevice.CreateSpriteFromFile(_T("�^�C�g����ʁi�C���j.png"));
	hp = GraphicsDevice.CreateSpriteFromFile(_T("HP�A�C�R�� (1).png"));
	end = GraphicsDevice.CreateSpriteFromFile(_T("�Q�[���I�[�o�[.png"));
	floor2 = GraphicsDevice.CreateSpriteFromFile(_T("5F.png"));
	clear = GraphicsDevice.CreateSpriteFromFile(_T("clear.png"));
	jump = GraphicsDevice.CreateSpriteFromFile(_T("nin_Jump.png"), Color(255, 255, 255));
	nin2 = GraphicsDevice.CreateSpriteFromFile(_T("nin2.png"), Color(255, 255, 255));
	nin2Left = GraphicsDevice.CreateSpriteFromFile(_T("nin2Left.png"), Color(255, 255, 255));
	ohiroma = GraphicsDevice.CreateSpriteFromFile(_T("��L��.png"));
	open = SoundDevice.CreateSoundFromFile(_T("open.wav"));
	close = SoundDevice.CreateSoundFromFile(_T("close.wav"));
	endtaiko = SoundDevice.CreateSoundFromFile(_T("clear.wav"));
	text = GraphicsDevice.CreateSpriteFont(_T("������ Demibold"), 60);
	text2 = GraphicsDevice.CreateSpriteFont(_T("������ Demibold"), 40);

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



//1�X�e
void GameMain::Initialize_1_3()
{ //1�X�e
		

		chara_x = 0; chara_y = 530; time = 0; frame = 0;
		kunai_x = chara_x, kunai_y = chara_y; //�U���p�N�i�C�̏������W
		floor1_1x = 0;//�w�i�̃X�N���[��
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

		text = GraphicsDevice.CreateSpriteFont(_T("������ Demibold"), 60);
		text2 = GraphicsDevice.CreateSpriteFont(_T("�l�r �o����"), 40);

		enemy_move_flg = false;
		enemy_move_flg2 = false;
		//�����܂�1�X�e
	}


void GameMain::Initialize_LastStage()
{ //�ŏI�X�e�[�W
	
	chara_x = 0; chara_y = 530;
	kunai_x = chara_x, kunai_y = chara_y; //�U���p�N�i�C�̏������W
	floor3_1x = 0;//�w�i�̃X�N���[��
	makimono_x = 750; makimono_y = 480;
	player_state = 0, jump_state = 0; player_frame = 0.0f;
	jumpspeed = 0; jumptime = 0; zahyou = 0; kunai_flag = false;
	ohiroma_flag = false;

	

	clear_flag = false;


	return;
}

//�ŏI�X�e�[�W









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
		//�G�����ړ�
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




		//�v���C���[&&�v���C���[�ړ�����
		if (game_scene == 1) {
			MainPlayer_1_3();
		}
		//�v���C���[&&�v���C���[�ړ�����
		if (game_scene == 3) {
			MainPlayer_LastStage();
		}

	}
	return 0;
}

//1�X�e
	void GameMain::MainPlayer_1_3()
	{   //1�X�e

		KeyboardState Key = Keyboard->GetState();
		KeyboardBuffer Key_buf = Keyboard->GetBuffer();
		//�ړ�



		if (Key.IsKeyDown(Keys_Right)) {
			player_state = 0;
			chara_x += 6.0f;
			floor1_1x -= 12.0f;

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

			jumptime = jumptime + 0.25;

			chara_y -= jumpspeed;

			chara_y = zahyou - (jumpspeed * jumptime - 0.5 * 9.80665 * jumptime * jumptime);

			if (chara_y > 530) {
				chara_y = 530;
				jump_state = 0;
			}
		}

		// �G�W�����v
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
		if (floor1_1x < -2560) {
			floor1_1x = -2560;
		}
		if (floor1_1x > -5) {
			chara_x = 0;
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
		kunai_x = chara_x + 100, kunai_y = chara_y + 50;
		//�G�@�\�@�U���p�N�i�C
		if (kunai_x > enemy_x + 100.0f - 20.0f || kunai_x + 8.0f < enemy_x ||
			kunai_y > enemy_y + 120.0f - 50.0f || kunai_y + 5.0f < enemy_y) {
			// �������Ă��Ȃ�
		}
		else {
			// �������Ă���
			if (Key.IsKeyDown(Keys_Space)) {
				hit_enemy_state = 1;
			}
		}

		//�G�@�\�@�U���p�N�i�C
		if (kunai_x > enemy_x2 + 60.0f - 10.0f || kunai_x + 8.0f < enemy_x2 ||
			kunai_y > enemy_y2 + 110.0f - 10.0f || kunai_y + 5.0f < enemy_y2) {
			// �������Ă��Ȃ�
		}
		else {
			// �������Ă���
			if (Key.IsKeyDown(Keys_Space)) {
				hit_enemy2_state = 1;
			}
		}
		if (hit_enemy_state == 0) {
			if (chara_x > enemy_x + 100.0f - 20.0f || chara_x + 80.0f - 30.0f < enemy_x ||
				chara_y > enemy_y + 120.0f - 50.0f || chara_y + 110.0f - 10.0f < enemy_y) {
				// �������Ă��Ȃ�
			}
			else {
				// �������Ă���
				hp_count = hp_count - 62;
			}
		}

		if (hit_enemy2_state == 0) {
			if (chara_x > enemy_x2 + 60.0f - 10.0f || chara_x + 80.0f - 30.0f < enemy_x2 ||
				chara_y > enemy_y2 + 110.0f - 10.0f || chara_y + 110.0f - 10.0f < enemy_y2) {
				// �������Ă��Ȃ�
			}
			else {
				// �������Ă���
				hp_count = hp_count - 62;
			}
		}
	}

//�ŏI�X�e�[�W
	void GameMain::MainPlayer_LastStage()
	{   //�ŏI�X�e�[�W

		KeyboardState Key = Keyboard->GetState();
		KeyboardBuffer Key_buf = Keyboard->GetBuffer();
		//�ړ�

		if (clear_flag == true && Key_buf.IsPressed(Keys_Enter)) {
			game_scene = 0;
		}

		if (ohiroma_flag == false && Key.IsKeyDown(Keys_Right)) {
			player_state = 0;
			chara_x += 3.0f;
			floor3_1x -= 12.0f;
		}


		// �W�����v
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


				//�G�@�\�@�v���C���[�����蔻��(�G�𕡐��\������\��B)
				if (hit_enemy_state == 0) {
					if (chara_x > enemy_x + 100.0f - 20.0f || chara_x + 80.0f - 30.0f < enemy_x ||
						chara_y > enemy_y + 120.0f - 50.0f || chara_y + 110.0f - 10.0f < enemy_y) {
						// �������Ă��Ȃ�
					}
					else {
						// �������Ă���
						enemyhit_count = 1;
					}
				}

				if (hit_enemy2_state == 0) {
					if (chara_x > enemy_x2 + 60.0f - 10.0f || chara_x + 80.0f - 30.0f < enemy_x2 ||
						chara_y > enemy_y2 + 110.0f - 10.0f || chara_y + 110.0f - 10.0f < enemy_y2) {
						// �������Ă��Ȃ�
					}
					else {
						// �������Ă���
						enemyhit_count = 1;
					}
				}

				//�K�i�����蔻��
				if (chara_x > floor1_1x + 3440.0f || chara_x + 200.0f - 70.0f < floor1_1x + 2600 ||
					chara_y > floor1_1y + 550.0f || chara_y + 250.0f - 10.0f < floor1_1y) {

				}
				else {
					kunai_flag = false;
					chara_y = -1.4f * chara_x + 1600;
					if (chara_y < 100.0f) {
						//�V�[���J�ڂ���v���O����
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

			//��L�ԓ˓�
			if (chara_x == 1150) {
				close->Play();
				ohiroma_flag = true;
				chara_x = 0;
				chara_y = 550;
			}

			//�w�i�ړ�����
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
			//�����܂�1�X�e


		//��L�Ԉړ�
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

			//��L�Ԉړ�����
			if (ohiroma_flag == true && clear_flag == false) {
				if (chara_x < 0) { chara_x = 0; }
				if (chara_x > 1150) { chara_x = 1150; }
				if (chara_y < 400) { chara_y = 400; }
				if (chara_y > 580) { chara_y = 580; }

				//�����[�v���C���[�̓����蔻��
				if (chara_x > makimono_x + 136.0f || chara_x + 128.0f - 80.0f < makimono_x ||
					chara_y > makimono_y + 184.0f || chara_y + 128.0f < makimono_y) {
					// �������Ă��Ȃ�
				}
				else {
					// �������Ă���
					clear_flag = true;
				}

				if (clear_flag == true) {
					endtaiko->Play();
				}

			}
		}
	}
//�����܂ōŏI�X�e�[�W






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

//1�X�e
void GameMain::Draw_1_3()
{  //1�X�e
	
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

//�ŏI�X�e�[�W
void GameMain::Draw_LastStage()
{  //�ŏI�X�e�[�W

	if (player_state == 0 && jump_state == 0 && ohiroma_flag == false) { SpriteBatch.Draw(*nin2Left, Vector3(chara_x, chara_y, -1)); }

	if (jump_state == 1) { SpriteBatch.Draw(*jump, Vector3(chara_x, chara_y, -1)); }

	SpriteBatch.Draw(*hp, Vector3(0, 0, -1), RectWH(hp_count, 0, -62, 60));

	if (ohiroma_flag == false) { SpriteBatch.Draw(*Right, Vector3(50, 140, -1)); }
	if (ohiroma_flag == false) { SpriteBatch.Draw(*Up, Vector3(50, 250, -1)); }

	
	if (ohiroma_flag == true) { SpriteBatch.Draw(*ohiroma, Vector3(0, 0, 0)); }

	KeyboardState Key = Keyboard->GetState();

	if (ohiroma_flag == true && player_state == 0) { SpriteBatch.Draw(*nin2Left, Vector3(chara_x, chara_y, -1)); }
	if (ohiroma_flag == true && player_state == 1) { SpriteBatch.Draw(*nin2, Vector3(chara_x, chara_y, -1)); }


	SpriteBatch.DrawString(text, Vector2(100, 10), Color_White, _T("%.0f�b"), time);
	if (clear_flag == true) { SpriteBatch.DrawString(text2, Vector2(200, 600), Color_White, _T("�^�C�g���ɖ߂邽��Enter�L�[������")); }
	if (clear_flag == true) { SpriteBatch.Draw(*clear, Vector3(250, 100, 0)); }

	SpriteBatch.Draw(*floor2, Vector3(floor1_1x, 0.0f, 0.0f));

	SpriteBatch.DrawString(text, Vector2(100, 10), Color_White, _T("%.0f�b"), time);

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

	//�G�ƃv���C���[�������������̏���
	if (enemyhit_count == 1) {

		enemyhit_count = 0;
	}
}




