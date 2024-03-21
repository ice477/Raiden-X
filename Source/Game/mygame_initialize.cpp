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
// �o��class���C�����C���}�Y�e������
/////////////////////////////////////////////////////////////////////////////

CGameStateInit::CGameStateInit(CGame *g) : CGameState(g)
{
}

void CGameStateInit::OnInit()
{
	//
	// ��ϫܦh�ɡAOnInit���J�Ҧ����ϭn��ܦh�ɶ��C���קK���C�����H
	//     �������@�СA�C���|�X�{�uLoading ...�v�A���Loading���i�סC
	//
	ShowInitProgress(0, "Start Initialize...");	// �@�}�l��loading�i�׬�0%
	//
	// �}�l���J���
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
	// ��OnInit�ʧ@�|����CGameStaterRun::OnInit()�A�ҥH�i���٨S��100%
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
	// ������GAME_STATE_RUN
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
