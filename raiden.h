#pragma once

#include <string>
#include <vector>
#include "../Library/gameutil.h"

using namespace std;
using namespace game_framework;

class Raiden {
public:
    enum Direction {
        STOP,
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
    CPoint GetCenter();
    void SetHeading(int next);
private:
    CMovingBitmap raiden; 

    Direction heading = STOP;
    bool alive = true;
    int type = 1;
    bool walkable = true;
    int speed = 3;
};

