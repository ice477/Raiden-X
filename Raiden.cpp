#include "stdafx.h"
#include "Raiden.h"

Raiden::Raiden() {
}

void Raiden::LoadBitmapByString(vector<string> path) {
	raiden.LoadBitmapByString({ path }, RGB(0, 0, 0));
}

void Raiden::SetStart(int nextlevel) {

}

void Raiden::SetPosition(int x, int y) {
	startpoint = CPoint(x, y);
	SetStart(level);
}


void Raiden::ShowBitmap() {
	if (isshow == true) {
		raiden.ShowBitmap();
	}
}

void Raiden::ChangeShow(bool show) {
	isshow = show;
}

void Raiden::SetAnimation() {
	raiden.SetFrameIndexOfBitmap(ani_now);
	if (!stop) {
		if (tick == 1) {
			tick = 0;
			if (ani_now >= ani_end) {
				ani_now = ani_start;
			}
			else {
				ani_now += 1;
			}
		}
		else {
			tick++;
		}
	}
}

void Raiden::CheckStop() {
	if (start) {
		stop = !walkable;
	}
}

void Raiden::Moving(bool walkable) {
	0;
}

CPoint Raiden::GetCenter() {
	CPoint center = CPoint((raiden.GetLeft() + (raiden.GetWidth() / 2) - delta), (raiden.GetTop() + (raiden.GetHeight() / 2) - delta));
	return center;
}

void Raiden::ClearAttack() {

}
