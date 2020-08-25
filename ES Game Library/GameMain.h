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
	SPRITE night;
	float enemy_x, enemy_y;
	float speed;
	int enemy_move_flg;
	int Game_Main_1_3_flg;
	int Game_scene_flg;
	int Game_scene_flg2;
	SPRITE clear;
	SPRITE ohiroma;
	SPRITE jump;
	SPRITE nin2, nin2Left;
	SPRITE enemy;
	SPRITE  player, leftplayer;
	SPRITE	kunai, kunai2;
	SPRITE floor, kaidan;
	SPRITE Right, Up;
	FONT text,text2;
	SOUND open,close, endtaiko;

	SPRITE Title;
	SPRITE GameOver;
	SPRITE Last;
	SPRITE hp1;

	SOUND se_End;
	SOUND se_Attack;
	SOUND se_start1;
	SOUND se_start2;

	float hp_x;
	float hp_count;
	int enemyhit_count;
	int game_scene;
	float chara_x, chara_y;
	float time;
	float frame;
	float  chara2_x, chara2_y;
	int player_state, jump_state, hit_state, shot_count, kunai_flag;
	float jumpspeed, jumptime, zahyou;
	float kunai_x, kunai_y, kunai2_x, kunai2_y;//�U���p�N�i�C
	float floor1_0x,floor1_1x, floor1_2x, kaidan1_x;
	float floor2_0x, floor2_1x, floor2_2x, kaidan2_x;
	float player_frame;

	//ANIMATIONMODEL player;
	//ANIMATIONMODEL leftplayer;
	//MODEL player_jump;
	//int player_jump_flg;

	CAMERA camera;

	float floor1_1y;
	float floor3_0x, floor3_1x, floor3_2x, kaidan3_x;
	enum { SHOT_MAX = 1 };
	int shot_flg[SHOT_MAX];
	float shot_x[SHOT_MAX];
	float shot_y[SHOT_MAX];
	float player_frame;
	float makimono_x, makimono_y;
	int ohiroma_flag, clear_flag;


	// �֐��錾
	void MainPlayer();
	void steage2();
	void MainPlayer_1_3();
	void Initialize_1_3();
	void Draw_1_3();
	
	void MainPlayer_LastStage();
	void Initialize_LastStage();
	void Draw_LastStage();

	void scene_change();
};