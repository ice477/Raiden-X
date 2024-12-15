#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "mygame.h"
#include <iostream>
#include <vector>
#include <cmath>


using namespace game_framework;


/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的遊戲執行物件，主要的遊戲程式都在這裡
/////////////////////////////////////////////////////////////////////////////

CGameStateRun::CGameStateRun(CGame *g) : CGameState(g)
{
	
}

CGameStateRun::~CGameStateRun()
{
	
}

void CGameStateRun::OnBeginState()
{
}

void CGameStateRun::OnMove()							// 移動遊戲元素
{
	if (!isPause) {
		int pspeed;
		if((isMovingUp&&isMovingLeft) || (isMovingUp&&isMovingRight) || (isMovingDown&&isMovingLeft) || (isMovingDown&&isMovingRight))
			pspeed = 5;
		else
			pspeed = 7;
		if (isMovingUp && !(raiden.GetTop() < 10)) {
			raiden.SetTopLeft(raiden.GetLeft(), raiden.GetTop() - pspeed);
		}
		if (isMovingLeft && !(raiden.GetLeft() < 5)) {
			raiden.SetTopLeft(raiden.GetLeft() - pspeed, raiden.GetTop());
		}
		if (isMovingDown && !(raiden.GetTop() > 400)) {
			raiden.SetTopLeft(raiden.GetLeft(), raiden.GetTop() + pspeed);
		}
		if (isMovingRight && !(raiden.GetLeft() > 320)) {
			raiden.SetTopLeft(raiden.GetLeft() + pspeed, raiden.GetTop());
		}

		if (playerAttack == true)
			PlayerIsAttack();



		for (auto it = pbullets.begin(); it != pbullets.end(); ) {
			it->SetTopLeft(it->GetLeft(), it->GetTop() - 30); 

			if (it->GetTop() < 0) {
				it = pbullets.erase(it);
			}
			else {
				++it;
			}
		}

		// 檢查玩家子彈是否與敵機發生碰撞
		for (size_t i = 0; i < pbullets.size(); ++i) {
			for (size_t j = 0; j < enemiesInfo.size(); ++j) {
				// 計算子彈與敵機中心之間的距離
				int bulletX = pbullets[i].GetLeft() + pbullets[i].GetWidth() / 2;
				int bulletY = pbullets[i].GetTop() + pbullets[i].GetHeight() / 2;
				int enemyX = enemiesInfo[j].bitmap.GetLeft() + enemiesInfo[j].bitmap.GetWidth() / 2;
				int enemyY = enemiesInfo[j].bitmap.GetTop() + enemiesInfo[j].bitmap.GetHeight() / 2;
				double distance = Distance(bulletX, bulletY, enemyX, enemyY);

				// 如果距離小於敵機判定半徑，則發生碰撞
				if (distance < enemiesInfo[j].size) {
					// 標記敵機為被擊中狀態
					enemiesInfo[j].hit = true;
					// 移除子彈
					pbullets.erase(pbullets.begin() + i);
					break; 
				}
			}
		}



		UpdateEnemies();
		UpdateEnemiesPosition();
	}
}

void CGameStateRun::OnInit()  								// 遊戲的初值及圖形設定
{
	lastBulletTime = GetTickCount();
	background.LoadBitmapByString({ "Resources/background/1.bmp" }, RGB(0, 0, 0));
	background.SetTopLeft(0, -3200);
	raiden.LoadBitmapByString({ "Resources/raiden/red/1.bmp" }, RGB(0, 0, 0));
	raiden.SetTopLeft(175,320);
	spark.LoadBitmapByString({ "Resources/spark/yellow2/3.bmp","Resources/spark/yellow2/1.bmp","Resources/spark/yellow2/2.bmp","Resources/spark/yellow2/4.bmp" }, RGB(0, 0, 0));
	spark.SetAnimation(10, false);




	//
	
}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	if (!isPause) {
		if (nChar == VK_UP) {
			isMovingUp = true;
		}
		if (nChar == VK_LEFT) {
			isMovingLeft = true;
		}
		if (nChar == VK_DOWN) {
			isMovingDown = true;
		}
		if (nChar == VK_RIGHT) {
			isMovingRight = true;
		}
		if (nChar == 0x5A) {
			playerAttack = true;
		}
		if (nChar == 0x58) {
			ClearAttack();
		}

		if (nChar == 0x50 || nChar == VK_RETURN) {
			isPause = true;
		}
	}
	else {
		if (nChar == 0x50 || nChar == VK_RETURN) {
			isPause = false;
		}
	}

}


void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == VK_UP) {
		isMovingUp = false;
	}
	if (nChar == VK_LEFT) {
		isMovingLeft = false;
	}
	if (nChar == VK_DOWN) {
		isMovingDown = false;
	}
	if (nChar == VK_RIGHT) {
		isMovingRight = false;
	}
	if (nChar == 0x5A) {
		playerAttack = false;
	}
}

void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
{
}

void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
}

void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
}

void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
{
}

void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
}

void CGameStateRun::OnShow()
{
	background.ShowBitmap();
	if (playerAttack == true)
		spark.ShowBitmap();
	raiden.ShowBitmap();
	for (auto& bullet : pbullets) {
		bullet.ShowBitmap();
	}
	
	Background_Scroll();


	//
	UpdateEnemies();

	
}


void CGameStateRun::Background_Scroll() {
	if (background.GetTop() >= 0 && !enemyCreated && !waitingForEnemy) {
		waitingForEnemy = true;
	}
	else if (isBoss() || isPause) {
		
	}
	else {
		background.SetTopLeft(background.GetLeft(), background.GetTop() + 1);
	}

}

bool CGameStateRun::isBoss() {
	return false;
}

void CGameStateRun::PlayerIsAttack() {
	
	DWORD currentTime = GetTickCount(); 

	
	if (currentTime - lastBulletTime >= 100) {  // 檢查是否距離上一次發射子彈的時間已經超過0.1秒
		spark.SetTopLeft(raiden.GetLeft() + 1, raiden.GetTop());
		bulletlevel = 1;   // 子彈等級
		pbullet.LoadBitmapByString({ "Resources/bullet/1.bmp", "Resources/bullet/2.bmp", "Resources/bullet/3.bmp" }, RGB(0, 0, 0));

		if (bulletlevel == 1) {
			pbullet.SetFrameIndexOfBitmap(0);
			pbullet.SetTopLeft(raiden.GetLeft() + 4, raiden.GetTop());
		}
		else if (bulletlevel == 2) {
			pbullet.SetFrameIndexOfBitmap(1);
			pbullet.SetTopLeft(raiden.GetLeft() + 1, raiden.GetTop());
		}
		else if (bulletlevel == 3) {
			pbullet.SetFrameIndexOfBitmap(2);
			pbullet.SetTopLeft(raiden.GetLeft() - 3, raiden.GetTop());
		}
		pbullets.push_back(pbullet); 

		lastBulletTime = currentTime; // 更新上一次發射子彈的時間
	}
}

void CGameStateRun::ClearAttack() {

}

void CGameStateRun::GameOver() {
	GotoGameState(GAME_STATE_OVER);
}



void CGameStateRun::CreateEnemy(EnemyType type, int x, int y) {
	int size = 0; // 預設大小
	int HP = 0; // 預設血量
	switch (type) {
	case Flyer:
		size = 30; // Flyer 敵機的預設大小為 20 像素
		HP = 1;
		break;
	case Bomber:
		size = 50; // Bomber 敵機的預設大小為 30 像素
		HP = 3;
		break;
	
	}

	CMovingBitmap enemy;
	switch (type) {
	case Flyer:
		enemy.LoadBitmapByString({ "Resources/flyer/1.bmp","Resources/flyer/2.bmp","Resources/flyer/3.bmp","Resources/flyer/4.bmp","Resources/flyer/5.bmp","Resources/flyer/6.bmp" }, RGB(0, 0, 0));
		break;
	case Bomber:
		enemy.LoadBitmapByString({ "Resources/bomber/1.bmp","Resources/bomber/2.bmp","Resources/bomber/3.bmp","Resources/bomber/4.bmp","Resources/bomber/5.bmp",
"Resources/bomber/6.bmp","Resources/bomber/7.bmp","Resources/bomber/8.bmp","Resources/bomber/9.bmp","Resources/bomber/10.bmp","Resources/bomber/11.bmp","Resources/bomber/12.bmp",
"Resources/bomber/13.bmp","Resources/bomber/14.bmp","Resources/bomber/15.bmp","Resources/bomber/16.bmp","Resources/bomber/17.bmp","Resources/bomber/18.bmp","Resources/bomber/19.bmp",
"Resources/bomber/20.bmp","Resources/bomber/21.bmp","Resources/bomber/22.bmp","Resources/bomber/23.bmp","Resources/bomber/24.bmp","Resources/bomber/25.bmp","Resources/bomber/26.bmp",
"Resources/bomber/27.bmp","Resources/bomber/28.bmp","Resources/bomber/29.bmp","Resources/bomber/30.bmp","Resources/bomber/31.bmp","Resources/bomber/32.bmp","Resources/bomber/33.bmp"}, RGB(0, 0, 0));
		break;
		// 添加其他敵機類型的情況...
	}


	//enemy.GetLeft() + enemy.GetWidth() / 2 + x,  enemy.GetTop() + enemy.GetHeight() / 2 + y
	enemy.SetTopLeft(x - enemy.GetWidth() / 2 ,-30 - enemy.GetHeight() / 2);
	enemies.push_back(enemy);
	enemiesInfo.push_back({ type, enemy, true, false, size, x,y,HP});
}


void CGameStateRun::EnemyHit(size_t enemyIndex) {
	if (enemyIndex < enemiesInfo.size()) {
		enemiesInfo[enemyIndex].hit = true;
	}
}


//
void CGameStateRun::UpdateEnemies() {
	for (size_t i = 0; i < enemiesInfo.size(); ++i) {
		if (!enemiesInfo[i].active) {
			enemiesInfo.erase(enemiesInfo.begin() + i);
		}
		else {
			enemiesInfo[i].bitmap.ShowBitmap();
			if (enemiesInfo[i].hit) {
				enemiesInfo[i].HP--;
				enemiesInfo[i].hit = false;
				if (enemiesInfo[i].HP == 0) {
					enemiesInfo[i].active = false;
				}
			}
		}
	}
}


void CGameStateRun::UpdateEnemiesPosition() {
	// 更新每個敵機的位置
	for (size_t i = 0; i < enemiesInfo.size(); ++i) {
		switch (enemiesInfo[i].type) {
		case Flyer:
			// 飛行型敵機的移動方式
			MoveFlyer(enemiesInfo[i]);
			break;
		case Bomber:
			// 轟炸機型敵機的移動方式
			MoveBomber(enemiesInfo[i]);
			break;
			// 添加其他敵機類型的情況...
		}
	}
}

void CGameStateRun::MoveFlyer(EnemyInfo& enemy) {
	if (enemy.bitmap.GetTop() < enemiesInfo[0].targetY) {
		enemy.bitmap.SetTopLeft(enemy.bitmap.GetLeft(), enemy.bitmap.GetTop() + 5);
	}
}

void CGameStateRun::MoveBomber(EnemyInfo& enemy) {
	static DWORD lastBulletTime = 0; // 記錄上次發射子彈的時間
	DWORD currentTime = GetTickCount(); // 獲取當前時間

	if (enemy.bitmap.GetTop() < enemiesInfo[0].targetY) {
		enemy.bitmap.SetTopLeft(enemy.bitmap.GetLeft(), enemy.bitmap.GetTop() + 2);
	}
	// 檢查是否已經超過1秒
	if (currentTime - lastBulletTime >= 1000) {
		lastBulletTime = currentTime;
		ShootBullet(enemy);
	}
}

void CGameStateRun::ShootBullet(EnemyInfo& enemy) {
	CMovingBitmap ebullet;
	ebullet.LoadBitmapByString({ "Resources/Ebullet/1.bmp" }, RGB(0, 0, 0));

	// 設置子彈的初始位置為轟炸機的中心
	int startX = static_cast<int>(enemy.bitmap.GetLeft() + enemy.bitmap.GetWidth() / 2);
	int startY = static_cast<int>(enemy.bitmap.GetTop() + enemy.bitmap.GetHeight() / 2);
	ebullet.SetTopLeft(startX, startY);

	// 添加子彈到敵機的子彈列表中
	ebullets.push_back(ebullet);
}


void CGameStateRun::UpdateEnemyBullets() {
	for (auto& enemy : enemiesInfo) {
		for (auto& ebullet : ebullets) {
			// 更新每個敵機的子彈位置
			// 這裡你可以添加對玩家子彈碰撞的檢測以及其他邏輯
			ebullet.SetTopLeft(ebullet.GetLeft(), ebullet.GetTop() + 3); // 這裡假設子彈向下移動
			ebullet.ShowBitmap(); // 顯示子彈
		}
	}
}