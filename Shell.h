#pragma once
#include"MyPoint.h"
#include"MySnake.h"
#include<vector>
class Shell : public MyPoint
{
public:
	friend class MySnake;
	Shell() {
		m_tmIni = GetTickCount64();
	};
	void Show(CDC* pDC);
	void SetDirStatus(bool flag) { DirIsSet = flag; };
	bool GetDirStatus() { return DirIsSet; };
	void SetDir(double dir) { nDir = dir; };
	double GetDir() { return nDir; };
	void SetSpeed(int speed) { nSpeed = speed; };
	double GetSpeed() { return nSpeed; };
	void UpdatePos(MySnake snake);
	bool HitFood(Food& food);
	bool HitStone(Stone& stone);
	void SetImg(CImage* pImg) 
	{ 
		m_pImg = pImg; 
	}

private:
	int nSpeed = 300;
	bool DirIsSet = false;
	double nDir = 0.0;
	__int64 m_tmIni;//创建的时刻
	
};

