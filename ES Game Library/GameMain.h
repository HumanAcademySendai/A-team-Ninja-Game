#pragma once

#include "ESGLib.h"
#include "GameScene/GameScene.hpp"

class GameMain : public CGameScene {
public:
	GameMain() : DefaultFont(GraphicsDevice.CreateDefaultFont())
	{
		//		ContentRootDirectory(_T("Content"));
	}

	virtual ~GameMain()
	{
#ifdef _INC_SQUIRREL
		Squirrel.ReleaseAllScripts();
#endif
#ifdef _INC_NUI
		NUI.ReleaseAllKinects();
#endif
#ifdef _INC_LIVE2D
		Live2D.ReleaseAllModels();
#endif
#ifdef _INC_EFFEKSEER
		Effekseer.ReleaseAllEffects();
#endif
#ifdef _INC_DIRECT2D
		Direct2D.ReleaseAllResources();
#endif
		MediaManager.ReleaseAllMedia();

		SoundDevice.ReleaseAllMusics();
		SoundDevice.ReleaseAllSounds();

		GraphicsDevice.ReleaseAllRenderTargets();
		GraphicsDevice.ReleaseAllStateBlocks();
		GraphicsDevice.ReleaseAllFonts();
		GraphicsDevice.ReleaseAllSprites();
		GraphicsDevice.ReleaseAllAnimationModels();
		GraphicsDevice.ReleaseAllModels();
		GraphicsDevice.ReleaseAllVertexBuffers();
		GraphicsDevice.ReleaseAllEffects();

		Finalize();
	}

public:
	virtual bool Initialize();

	virtual int  Update();
	virtual void Draw();

private:
	void Finalize();
	FONT DefaultFont;

private:
	// �ϐ��錾
	SPRITE Space, Right, Up;
	SPRITE enemy;
	SPRITE  player, leftplayer;
	SPRITE	kunai, kunai2;
	SPRITE floor, kaidan;
	FONT text,text2;
	float enemy_x, enemy_y;
	float enemy_x2, enemy_y2;

	float speed;
	int enemy_move_flg;
	int enemy_move_flg2;
	int Game_Main_1_3_flg;
	int Game_scene_flg;
	int Game_scene_flg2;



	float  chara_x, chara_y;
	int player_state, jump_state, shot_count, kunai_flag,game_scene;
	int  hit_enemy_state, hit_enemy2_state, jump_enemy_state;
	int player_hit_state; //�G�Ɠ����������̏���
	float time;
	float frame;
	float jumpspeed, jumptime, zahyou;
	float enemy_jumpspeed, enemy_jumptime, enemy_zahyou;
	float kunai_x, kunai_y;//�U���p�N�i�C
	float floor1_1x,floor1_1y;
	float floor2_0x, floor2_1x, floor2_2x;
	float kaidan1_x, kaidan1_y, kaidan2_x, kaidan2_y;

	// �֐��錾
	void MainPlayer_1_3();
	void Initialize_1_3();
	void Draw_1_3();
	
};