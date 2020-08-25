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

	SPRITE Space;
	SPRITE clear;
	SPRITE ohiroma;
	SPRITE nin2, nin2Left;
	SPRITE enemy;
	SPRITE  leftplayer;
	SPRITE Right, Up;
	FONT text, text2;
	SOUND open, close, endtaiko;
	SPRITE Title;
	SPRITE end;
	SPRITE hp;
	SPRITE  player, jump;
	SPRITE ene_nin;
	SPRITE	kunai, kunai2;
	SPRITE floor,floor2, kaidan;
	float enemy_x, enemy_y;
	float enemy_x2, enemy_y2;

	float speed;
	int enemy_move_flg;
	int enemy_move_flg2;
	int clear_flag;



	float  chara_x, chara_y;
	int player_state, jump_state, shot_count, kunai_flag,game_scene;
	int  hit_enemy_state, hit_enemy2_state;//0・・当たってない	1・・当たってる
	int jump_enemy_state;
	int enemyhit_count; //敵と当たった時の処理
	float enemy_jumpspeed, enemy_jumptime, enemy_zahyou;
	float floor1_1x,floor1_1y;
	float floor2_0x, floor2_1x, floor2_2x;

	float hp_count;
	float time;
	float player_frame;
	float frame;
	float jumpspeed, jumptime, zahyou;
	float kunai_x, kunai_y;//攻撃用クナイ
	float floor3_1x;
	float makimono_x, makimono_y;
	int ohiroma_flag;


	// 関数宣言
	void Draw_1_3();
	void MainPlayer_1_3();
	void  Initialize_1_3();
	void MainPlayer_LastStage();
	void Initialize_LastStage();
	void Draw_LastStage();
	void MainPlayer_1_3();
	void Initialize_1_3();
	void Draw_1_3();


};