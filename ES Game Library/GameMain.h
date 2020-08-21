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
	SPRITE ohiroma;
	SPRITE smallnin,smallnin2;
	SPRITE makimono;
	SPRITE enemy;
	SPRITE  player, leftplayer;
	SPRITE	kunai, kunai2;
	SPRITE floor, kaidan;
	FONT text;

	float speed;
	int enemy_move_flg;
	int enemy_move_flg2;
	int Game_Main_1_3_flg;
	int Game_scene_flg;
	int Game_scene_flg2;



	float  chara_x, chara_y;
	int player_state, jump_state, kunai_flag;
	float time;
	float frame;
	float jumpspeed, jumptime, zahyou;
	float kunai_x, kunai_y;//攻撃用クナイ
	float floor3_1x;
	float makimono_x, makimono_y;
	int ohiroma_flag;


	// 関数宣言
	void MainPlayer_LastStage();
	void Initialize_LastStage();
	void Draw_LastStage();

};