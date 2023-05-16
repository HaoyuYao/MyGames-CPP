#pragma once
#include"MyPoint.h"
#include<list>
class Stone
{
public:
	friend class MySnake;//ÓÑÔªÀà
	friend class Shell;
	friend class CGreedySnakeView;
	Stone()
	{
		const int SCREEN_CX = 2462;
		const int SCREEN_CY = 1378;
		int heightX = SCREEN_CX;
		int heightY = SCREEN_CY;
		srand((int)time(0));
		for (int i = 0; i < 8; i++)
		{
			MyPoint pt;
			pt.SetSize(i*20+100);
			pt.Setx(rand() % heightX+100);
			pt.Sety(rand() % heightY+100);
			stone.emplace_back(pt);
		}
	}
	void Show(CDC* pDC)
	{
		for (auto& pt : stone)
		{
			if (pt.m_pImg == nullptr || pt.m_pImg->IsNull())
				pDC->Ellipse(pt.m_x - pt.m_nSize / 2, pt.m_y - pt.m_nSize / 2, pt.m_x + pt.m_nSize / 2, pt.m_y + pt.m_nSize / 2);
			else
			{
				pt.m_pImg->Draw(pDC->m_hDC,
					CRect(pt.m_x - pt.m_nSize / 2, pt.m_y - pt.m_nSize / 2, pt.m_x + pt.m_nSize / 2, pt.m_y + pt.m_nSize / 2),
					CRect(0, 0, pt.m_pImg->GetWidth(), pt.m_pImg->GetHeight())
				);
			}
		}
		

	}
private:
	std::list<MyPoint> stone;
};

