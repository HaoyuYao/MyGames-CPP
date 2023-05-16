#include "pch.h"
#include "Shell.h"
void Shell::UpdatePos(MySnake snake)
{

	__int64 tmCurrent = GetTickCount64();
	int nDis = nSpeed * (tmCurrent - m_tmIni) * 0.001;//毫秒除以1000为妙
	if (!GetDirStatus())
	{
		this->SetDir(snake.GetDir());
		SetDirStatus(true);
	}
	Setx(m_x + nDis * cos(this->GetDir()));
	Sety(m_y + nDis * sin(this->GetDir()));
	m_tmIni = tmCurrent;
}
void Shell::Show(CDC *pDC)
{
	if (m_pImg == nullptr || m_pImg->IsNull())
		pDC->Ellipse(m_x - m_nSize / 2, m_y - m_nSize / 2, m_x + m_nSize / 2, m_y + m_nSize / 2);
	else
	{
		m_pImg->Draw(pDC->m_hDC,
			CRect(m_x - m_nSize / 2, m_y - m_nSize / 2, m_x + m_nSize / 2, m_y + m_nSize / 2),
			CRect(0, 0, m_pImg->GetWidth(), m_pImg->GetHeight())
		);
	}
}
bool Shell::HitFood(Food& fd)
{
	MyPoint newTail;
	MyPoint shell = *this;
	auto iter = fd.food.begin();
	while (iter != fd.food.end())
	{
		if ((*iter) && shell)
		{
			fd.food.erase(iter);
			return true;//一旦碰撞上就要及时return，因为food的size会立刻改变，并且也没有继续遍历的必要
		}
		iter++;
	}
	return false;
}
bool Shell::HitStone(Stone& st)
{
	MyPoint shell = *this;
	auto iter = st.stone.begin();
	while (iter != st.stone.end())
	{
		if ((*iter) && shell)
		{
			st.stone.erase(iter);
			return true;//一旦碰撞上就要及时return，因为food的size会立刻改变，并且也没有继续遍历的必要
		}
		iter++;
	}
	return false;
}
