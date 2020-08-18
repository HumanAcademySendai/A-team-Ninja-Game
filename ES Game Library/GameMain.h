
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
	float enemy_x, enemy_y;
	float speed;
	int enemy_move_flg;


	SPRITE  player, leftplayer, kunai, kunai2, floor, kaidan;
	float  chara_x, chara_y;
	int player_state, jump_state, hit_state, shot_count, kunai_flag;
	float jumpspeed, jumptime, zahyou;
	float kunai_x, kunai_y, kunai2_x, kunai2_y;//攻撃用クナイ
	float floor1_0x,floor1_1x, floor1_2x, kaidan1_x;
	enum { SHOT_MAX = 1 };
	int shot_flg[SHOT_MAX];
	float shot_x[SHOT_MAX];
	float shot_y[SHOT_MAX];
	// 関数宣言
	void MainPlayer();
	void steage2();
};