#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "mygame.h"

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
		if (isMovingUp && !(raiden.GetTop() < 10)) {
			raiden.SetTopLeft(raiden.GetLeft(), raiden.GetTop() - 5);
		}
		if (isMovingLeft && !(raiden.GetLeft() < 5)) {
			raiden.SetTopLeft(raiden.GetLeft() - 5, raiden.GetTop());
		}
		if (isMovingDown && !(raiden.GetTop() > 400)) {
			raiden.SetTopLeft(raiden.GetLeft(), raiden.GetTop() + 5);
		}
		if (isMovingRight && !(raiden.GetLeft()> 320)) {
			raiden.SetTopLeft(raiden.GetLeft() + 5, raiden.GetTop());
		}

		if (playerAttack == true)
			PlayerIsAttack();
	}

}

void CGameStateRun::OnInit()  								// 遊戲的初值及圖形設定
{
	background.LoadBitmapByString({ "Resources/background/1.bmp" }, RGB(0, 0, 0));
	background.SetTopLeft(0, -3200);
	raiden.LoadBitmapByString({ "Resources/raiden/red/1.bmp" }, RGB(0, 0, 0));
	raiden.SetTopLeft(175,400);
	spark.LoadBitmapByString({ "Resources/spark/yellow2/1.bmp","Resources/spark/yellow2/2.bmp","Resources/spark/yellow2/3.bmp","Resources/spark/yellow2/4.bmp" }, RGB(0, 0, 0));
	spark.SetAnimation(10, false);
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
	raiden.ShowBitmap();
	Background_Scroll();
}

void CGameStateRun::Background_Scroll() {
	if (background.GetTop() >= 0 || isBoss() || isPause) {
		
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
	
	spark.ShowBitmap();
}

void CGameStateRun::ClearAttack() {

}