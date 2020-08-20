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
	// 変数宣言
	SPRITE night;
	SPRITE enemy;
	SPRITE  player, leftplayer;
	SPRITE	kunai, kunai2;
	SPRITE floor, kaidan;
	FONT text;
	float enemy_x, enemy_y;
	float enemy_x2, enemy_y2;

	float speed;
	int enemy_move_flg;
	int enemy_move_flg2;
	int Game_Main_1_3_flg;
	int Game_scene_flg;
	int Game_scene_flg2;



	float  chara_x, chara_y;
	int player_state, jump_state, hit_state, shot_count, kunai_flag,game_scene;
	float time;
	float frame;
	float jumpspeed, jumptime, zahyou;
	float kunai_x, kunai_y, kunai2_x, kunai2_y;//攻撃用クナイ
	float floor1_1x,floor1_1y;
	float floor2_0x, floor2_1x, floor2_2x;
	float kaidan1_x, kaidan1_y, kaidan2_x, kaidan2_y;
	enum { SHOT_MAX = 1 };
	int shot_flg[SHOT_MAX];
	float shot_x[SHOT_MAX];
	float shot_y[SHOT_MAX];
	// 関数宣言
	void MainPlayer_1_3();
	void Initialize_1_3();
	void Draw_1_3();
	
};