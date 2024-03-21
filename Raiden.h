#pragma once

#include <string>
#include <vector>
#include "../Library/gameutil.h"

using namespace std;
using namespace game_framework;

class Raiden {
public:
	enum Direction {
		UP,
		LEFT,
		DOWN,
		RIGHT
	};

	Raiden();
	void LoadBitmapByString(vector<string> path);
	void ShowBitmap();
	void Moving(bool walkable);
	void SetAnimation();
	void CheckStop();
	CPoint GetCenter();
	void SetPosition(int x, int y);
	void SetStart(int nextlevel);
	void ChangeShow(bool show);
	void ClearAttack();

private:
	int level = 1;
	CMovingBitmap raiden;
	vector<string> path;
	Direction facing = LEFT;
	Direction next_facing = LEFT;
	bool walkable = true;
	bool turnable = false;
	bool start = false;
	bool stop = true;
	bool isshow = true;
	int normalspeed = 75;				// ���`�t�� (pix/sec)
	int nowspeed;						// �ثe�t�� (pix/sec)
	double speedrate = 0.8;				// �t�פ�� 
	int move = 0;						// �s�C�@�V�ݭn���h�� pix
	int moremove = 0;					// �s�ݭn�X�ӴV�h���@�� pix
	int nextmove = 2;
	int morecount = 0;
	int movecount = 1;					// �p��@�����F�X�V
	int tick = 0;						// �p��C��V���U�@�ӹϤ�
	int delta = 12;
	int ani_start = 4;
	int ani_end = 7;
	int ani_now = 4;
	CPoint startpoint;
};
