#pragma once
#include<deque>
#include"MyPoint.h"
#include"Food.h"
#include"Shell.h"
#include"Stone.h"
class MySnake
{
public:
    friend class CGreedySnakeView;
    MySnake() 
    {
       
    }
    void InitSnake()//初始化蛇
    {
        if(IsHuman)
        for (int i = 0; i < 5; i++)
            snake.emplace_back(14 + i * 50, 8);
        else
            snake.emplace_back(rand() % 2462, rand() % 1378);
    }
    void pMoveTo(MyPoint pDir);
    void SetDir(double dir) { nDir = dir; };
    double GetDir() { return nDir; };
    bool GetStatus() { return IsHuman; };
    void SetStatus(bool flag) { IsHuman = flag; };
	void Show(CDC* pDC)//显示蛇
	{

       
        if (!snake.empty())
        {
            auto iter = snake.begin();
            for (int i = 0; i < snake.size(); i++, iter++)
            {
                COLORREF color = i == 0 ? RGB(255, 105, 100) : RGB(255, 105, 180);
                if (i == snake.size() - 1)
                    color = RGB(255, 0, 0);//头部

                CBrush brush(color);
                if (IsHuman)
                {

                    CPen penRainbow(PS_SOLID, 2, RGB(255, 192, 203));
                    CPen* pOldPen = pDC->SelectObject(&penRainbow);
                    pDC->SelectObject(&brush);
                    pDC->Ellipse(int((*iter).Getx() - (*iter).GetSize() / 2), int((*iter).Gety() - (*iter).GetSize() / 2), int((*iter).Getx() + (*iter).GetSize() / 2), int((*iter).Gety() + (*iter).GetSize() / 2));
                }
                else
                {
                    CPen penRainbow(PS_SOLID, 2, RGB(255, 255, 0));
                    CPen* pOldPen = pDC->SelectObject(&penRainbow);
                    CBrush brush(RGB(255, 165, 0));
                    pDC->SelectObject(&brush);
                    pDC->Ellipse(int((*iter).Getx() - (*iter).GetSize() / 2), int((*iter).Gety() - (*iter).GetSize() / 2), int((*iter).Getx() + (*iter).GetSize() / 2), int((*iter).Gety() + (*iter).GetSize() / 2));
                }
               
            }
        }

	}
    bool HitItself();//碰撞检测
    void EatFood(Food& food);
    bool HitStone(Stone& stone);
    MyPoint AutoFindFood(Food& food);
    Shell Fire();
    ~MySnake()
    {
        snake.clear();
    }
    
private:
    std::deque<MyPoint> snake;
    bool IsHuman = true;
    double nDir=0.0;
    
};

