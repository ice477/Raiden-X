#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include <fstream>
#include <sstream>
#include "mygame.h"


using namespace game_framework;

std::vector<CMovingBitmap> bullets;


DWORD lastBulletTime = 0;

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
		if (isMovingUp && !(raiden.GetTop() < 10)) {
			raiden.SetTopLeft(raiden.GetLeft(), raiden.GetTop() - 7);
		}
		if (isMovingLeft && !(raiden.GetLeft() < 5)) {
			raiden.SetTopLeft(raiden.GetLeft() - 7, raiden.GetTop());
		}
		if (isMovingDown && !(raiden.GetTop() > 400)) {
			raiden.SetTopLeft(raiden.GetLeft(), raiden.GetTop() + 7);
		}
		if (isMovingRight && !(raiden.GetLeft() > 320)) {
			raiden.SetTopLeft(raiden.GetLeft() + 7, raiden.GetTop());
		}

		if (playerAttack == true)
			PlayerIsAttack();

		if (playerAttack == true)
			PlayerIsAttack();

		for (auto& bullet : bullets) {
			bullet.SetTopLeft(bullet.GetLeft(), bullet.GetTop() - 30); // 假設子彈向上移動
		}
	}
}

void CGameStateRun::OnInit()  								// 遊戲的初值及圖形設定
{
	lastBulletTime = GetTickCount();
	background.LoadBitmapByString({ "Resources/background/1.bmp" }, RGB(0, 0, 0));
	background.SetTopLeft(0, -3200);
	raiden.LoadBitmapByString({ "Resources/raiden/red/1.bmp" }, RGB(0, 0, 0));
	raiden.SetTopLeft(175,400);
	spark.LoadBitmapByString({ "Resources/spark/yellow2/1.bmp","Resources/spark/yellow2/2.bmp","Resources/spark/yellow2/3.bmp","Resources/spark/yellow2/4.bmp" }, RGB(0, 0, 0));
	spark.SetAnimation(10, false);
	flyer.LoadBitmapByString({ "Resources/flyer/1.bmp","Resources/flyer/2.bmp" ,"Resources/flyer/3.bmp" ,"Resources/flyer/4.bmp" ,"Resources/flyer/5.bmp" ,"Resources/flyer/6.bmp" }, RGB(0, 0, 0));

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
	for (auto& bullet : bullets) {
		bullet.ShowBitmap();
	}
	Background_Scroll();
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
	spark.SetTopLeft(raiden.GetLeft() + 1, raiden.GetTop());
	DWORD currentTime = GetTickCount(); 

	
	if (currentTime - lastBulletTime >= 100) {  // 檢查是否距離上一次發射子彈的時間已經超過0.1秒
		CMovingBitmap bullet; 
		bulletlevel = 3;   // 子彈等級
		bullet.LoadBitmapByString({ "Resources/bullet/1.bmp", "Resources/bullet/2.bmp", "Resources/bullet/3.bmp" }, RGB(0, 0, 0));

		if (bulletlevel == 1) {
			bullet.SetFrameIndexOfBitmap(0);
			bullet.SetTopLeft(raiden.GetLeft() + 4, raiden.GetTop());
		}
		else if (bulletlevel == 2) {
			bullet.SetFrameIndexOfBitmap(1);
			bullet.SetTopLeft(raiden.GetLeft() + 1, raiden.GetTop());
		}
		else if (bulletlevel == 3) {
			bullet.SetFrameIndexOfBitmap(2);
			bullet.SetTopLeft(raiden.GetLeft() - 3, raiden.GetTop());
		}
		bullets.push_back(bullet); 

		lastBulletTime = currentTime; // 更新上一次發射子彈的時間
	}
}

void CGameStateRun::ClearAttack() {

}

void CGameStateRun::GameOver() {
	GotoGameState(GAME_STATE_OVER);
}

void CGameStateRun::BulletChoose() {
	
		
}