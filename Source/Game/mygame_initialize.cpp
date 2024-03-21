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
// 這個class為遊戲的遊戲開頭畫面物件
/////////////////////////////////////////////////////////////////////////////

CGameStateInit::CGameStateInit(CGame *g) : CGameState(g)
{
}

void CGameStateInit::OnInit()
{
	//
	// 當圖很多時，OnInit載入所有的圖要花很多時間。為避免玩遊戲的人
	//     等的不耐煩，遊戲會出現「Loading ...」，顯示Loading的進度。
	//
	ShowInitProgress(0, "Start Initialize...");	// 一開始的loading進度為0%
	//
	// 開始載入資料
	//
	menu.LoadBitmapByString({	"Resources/menu/1.bmp", "Resources/menu/2.bmp", "Resources/menu/3.bmp", "Resources/menu/4.bmp", "Resources/menu/5.bmp",
								"Resources/menu/6.bmp", "Resources/menu/7.bmp", "Resources/menu/8.bmp", "Resources/menu/9.bmp", "Resources/menu/10.bmp",
								"Resources/menu/11.bmp", "Resources/menu/12.bmp", "Resources/menu/13.bmp", "Resources/menu/14.bmp", "Resources/menu/15.bmp",
								"Resources/menu/16.bmp", "Resources/menu/17.bmp", "Resources/menu/18.bmp", "Resources/menu/19.bmp", "Resources/menu/20.bmp",
								"Resources/menu/21.bmp", "Resources/menu/22.bmp", "Resources/menu/23.bmp", "Resources/menu/24.bmp", "Resources/menu/25.bmp",
								"Resources/menu/26.bmp", "Resources/menu/27.bmp", "Resources/menu/28.bmp", "Resources/menu/29.bmp", "Resources/menu/30.bmp",
								"Resources/menu/31.bmp", "Resources/menu/32.bmp", "Resources/menu/33.bmp", "Resources/menu/34.bmp", "Resources/menu/35.bmp",
								"Resources/menu/36.bmp", "Resources/menu/37.bmp", "Resources/menu/38.bmp", "Resources/menu/39.bmp"
		}, RGB(0, 0, 0));
	menu.SetTopLeft(10, 250);
	// 此OnInit動作會接到CGameStaterRun::OnInit()，所以進度還沒到100%
	//
}

void CGameStateInit::OnBeginState()
{
}

void CGameStateInit::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == VK_SPACE || nChar == VK_RETURN) {
		if(phase ==1)
			GotoGameState(GAME_STATE_RUN);
		else if (phase == 2) {
			
		}
		else if (phase == 3) {

		}
	}
	else if (nChar == VK_DOWN) {
		phase++;
		if (phase == 4)
			phase = 1;
	}
	else if (nChar == VK_UP) {
		phase--;
		if (phase == 0)
			phase = 3;
	}
}

void CGameStateInit::OnLButtonDown(UINT nFlags, CPoint point)
{
	// 切換至GAME_STATE_RUN
}

void CGameStateInit::OnShow()
{
	phase_execution();
	show_homepage();
	
}

void CGameStateInit::show_homepage() {
	menu.ShowBitmap();
}

void CGameStateInit::phase_execution() {
	if (phase == 1)
		menu.SetFrameIndexOfBitmap(0);
	else if (phase == 2)
		menu.SetFrameIndexOfBitmap(1);
	else if (phase ==3)
		menu.SetFrameIndexOfBitmap(2);
}
