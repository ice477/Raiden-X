#include "stdafx.h"
#include "raiden.h"


Raiden::Raiden() {
}

void Raiden::LoadBitmapByString(vector<string> path) {
	raiden.LoadBitmapByString({ path }, RGB(0, 0, 0));
}

void Raiden::ShowBitmap() {
	if (alive == true) {
		raiden.ShowBitmap();
	}
}

void Raiden::Moving(bool walkable) {
	this->walkable = walkable;
	if (walkable) {
		if (heading == 1) {
			raiden.SetTopLeft(raiden.GetLeft(), raiden.GetTop() - speed);
		}else if (heading == 2) {
			raiden.SetTopLeft(raiden.GetLeft() - speed, raiden.GetTop() );
		}if (heading == 3) {
			raiden.SetTopLeft(raiden.GetLeft() - speed, raiden.GetTop());
		}
	}
}



CPoint Raiden::GetCenter() {
	CPoint center = CPoint((raiden.GetLeft() + (raiden.GetWidth() / 2) ), (raiden.GetTop() + (raiden.GetHeight() / 2)));
	return center;
}

void Raiden::SetHeading(int next) {
	heading = Direction(next);
}