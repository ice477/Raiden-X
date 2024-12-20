/*
 * mygame.h: 本檔案儲遊戲本身的class的interface
 * Copyright (C) 2002-2008 Woei-Kae Chen <wkc@csie.ntut.edu.tw>
 *
 * This file is part of game, a free game development framework for windows.
 *
 * game is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * game is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 *	 2004-03-02 V4.0
 *      1. Add CGameStateInit, CGameStateRun, and CGameStateOver to
 *         demonstrate the use of states.
 *   2005-09-13
 *      Rewrite the codes for CBall and CEraser.
 *   2005-09-20 V4.2Beta1.
 *   2005-09-29 V4.2Beta2.
 *   2006-02-08 V4.2
 *      1. Rename OnInitialUpdate() -> OnInit().
 *      2. Replace AUDIO_CANYON as AUDIO_NTUT.
 *      3. Add help bitmap to CGameStateRun.
 *   2006-09-09 V4.3
 *      1. Rename Move() and Show() as OnMove and OnShow() to emphasize that they are
 *         event driven.
 *   2008-02-15 V4.4
 *      1. Add namespace game_framework.
 *      2. Replace the demonstration of animation as a new bouncing ball.
 *      3. Use ShowInitProgress(percent) to display loading progress.
*/
#include <vector>

#include <fstream>

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// Constants
	/////////////////////////////////////////////////////////////////////////////

	enum AUDIO_ID {				// 定義各種音效的編號
		AUDIO_DING,				// 0
		AUDIO_LAKE,				// 1
		AUDIO_NTUT				// 2
	};

	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的遊戲開頭畫面物件
	// 每個Member function的Implementation都要弄懂
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateInit : public CGameState {
	public:
		CGameStateInit(CGame *g);
		void OnInit();  								// 遊戲的初值及圖形設定
		void OnBeginState();							// 設定每次重玩所需的變數
		void OnKeyUp(UINT, UINT, UINT); 				// 處理鍵盤Up的動作
		void OnLButtonDown(UINT nFlags, CPoint point);  // 處理滑鼠的動作
	protected:
		void OnShow();									// 顯示這個狀態的遊戲畫面
	private:
		int phase = 1;
		CMovingBitmap logo;								// csie的logo	
		CMovingBitmap menu;
		void show_homepage();
		void phase_execution();
	};

	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的遊戲執行物件，主要的遊戲程式都在這裡
	// 每個Member function的Implementation都要弄懂
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateRun : public CGameState {
	public:
		CGameStateRun(CGame *g);
		~CGameStateRun();
		void OnBeginState();							// 設定每次重玩所需的變數
		void OnInit();  								// 遊戲的初值及圖形設定
		void OnKeyDown(UINT, UINT, UINT);
		void OnKeyUp(UINT, UINT, UINT);
		void OnLButtonDown(UINT nFlags, CPoint point);  // 處理滑鼠的動作
		void OnLButtonUp(UINT nFlags, CPoint point);	// 處理滑鼠的動作
		void OnMouseMove(UINT nFlags, CPoint point);	// 處理滑鼠的動作 
		void OnRButtonDown(UINT nFlags, CPoint point);  // 處理滑鼠的動作
		void OnRButtonUp(UINT nFlags, CPoint point);	// 處理滑鼠的動作

		
	protected:
		void OnMove();									// 移動遊戲元素
		void OnShow();									// 顯示這個狀態的遊戲畫面
	private:
		int stage;
		int bulletlevel;
		
		bool isMovingUp = false;
		bool isMovingLeft = false;
		bool isMovingDown = false;
		bool isMovingRight = false;
		bool isPause = false;
		bool playerAttack = false;
		bool enemyCreated = false;
		bool waitingForEnemy = false;
		bool animated = false;

		CMovingBitmap background;
		CMovingBitmap raiden;
		CMovingBitmap spark;

		CMovingBitmap pbullet;
		std::vector<CMovingBitmap> pbullets;

		CMovingBitmap ebullet;
		std::vector<CMovingBitmap> ebullets;

		DWORD lastBulletTime = 0;

		std::vector<CMovingBitmap> enemies; // 敵機向量
		std::vector<DWORD> enemyStartTime; // 追蹤每個敵機開始行動的時間
		std::vector<size_t> enemiesToRemove;
		
		enum EnemyType {
			Flyer,
			Bomber
		};

		struct EnemyInfo {
			EnemyType type;        // 敵機類型
			CMovingBitmap bitmap;  // 敵機圖像
			bool active;           // 敵機是否活動中
			bool hit;              // 敵機是否被擊中
			int size;              // 敵機的大小，用於碰撞檢測
			int targetX;
			int targetY;
			int HP;
		};
		std::vector<EnemyInfo> enemiesInfo;

		double Distance(int x1, int y1, int x2, int y2) {
			return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
		}

		CMovingBitmap flyer;
		CMovingBitmap bomber;
		CMovingBitmap vtank;
		CMovingBitmap htank;
		CMovingBitmap gtank;
		CMovingBitmap tank3;

		void Background_Scroll();
		bool isBoss();
		void PlayerIsAttack();
		void ClearAttack();
		void GameOver();
		void CreateEnemy(EnemyType type, int x, int y);
		void EnemyHit(size_t enemyIndex);

		void UpdateEnemies();
		void UpdateEnemiesPosition();
		void MoveFlyer(EnemyInfo& enemy);
		void MoveBomber(EnemyInfo& enemy);

		void ShootBullet(EnemyInfo& enemy);
		void UpdateEnemyBullets();
	};

	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的結束狀態(Game Over)
	// 每個Member function的Implementation都要弄懂
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateOver : public CGameState {
	public:
		CGameStateOver(CGame *g);
		void OnBeginState();							// 設定每次重玩所需的變數
		void OnInit();
	protected:
		void OnMove();									// 移動遊戲元素
		void OnShow();									// 顯示這個狀態的遊戲畫面
	private:
		int counter;	// 倒數之計數器
	};

}
