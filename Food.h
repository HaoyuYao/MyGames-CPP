#pragma once
#include"MyPoint.h"
#include<list>
const int SCREEN_CX = 2462;
const int SCREEN_CY = 1378;
class Food
{
public:
	friend class MySnake;//友元类
	friend class Shell;
	friend class CGreedySnakeView;
	Food()
	{
		int heightX = SCREEN_CX;
		int heightY = SCREEN_CY;
		srand((int)time(0));
		for (int i = 0; i < 200; i++)
		{
			MyPoint pt;
			pt.Setx(rand() % heightX);
			pt.Sety(rand() % heightY);
			food.emplace_back(pt);
		}
	}
	void Show(CDC* pDC)
	{
		COLORREF colors[] = {RGB(255, 0, 0), RGB(255, 127, 0), RGB(255, 255, 0),
						 RGB(0, 255, 0), RGB(0, 0, 255),RGB(0, 255, 255) ,RGB(75, 0, 130)};

		int tag = 0;//记录每个点的“特征”

		for (auto& pt : food)
		{
			tag = (pt.Getx() + pt.Gety()) / 5;
			pt.SetSize(30 + (tag % 5) * 5);
			CBrush brush(colors[tag % 7]);
			CPen penRainbow(PS_SOLID, 2, colors[tag % 7]);
			CPen* pOldPen = pDC->SelectObject(&penRainbow);
			pDC->SelectObject(&brush);
			pDC->Ellipse(int(pt.Getx() - pt.GetSize() / 2), int(pt.Gety() - pt.GetSize() / 2), int(pt.Getx() + pt.GetSize() / 2), int(pt.Gety() + pt.GetSize() / 2));
		}
		
	}
private:
	std::list<MyPoint> food;


};

