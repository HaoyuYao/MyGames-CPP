#pragma once
class MyPoint
{
public:
	friend class Food;
	friend class MySnake;
	friend class Stone;
	MyPoint() {};
	MyPoint(int x, int y) { m_x = x, m_y = y; };
	void Setx(double x) { m_x = x; };
	double Getx() { return m_x; };
	void Sety(double y) { m_y = y; };
	double Gety() { return m_y; };
	void SetSize(double size) { m_nSize = size; };
	double GetSize() { return m_nSize; };
	bool operator && (MyPoint &pt) {
		const double error = 1.5;
		double distance = sqrt(((*this).Getx() - pt.Getx()) * ((*this).Getx() - pt.Getx()) + ((*this).Gety() - pt.Gety()) * ((*this).Gety() - pt.Gety()));
		if (distance <((*this).GetSize() / 2 + pt.GetSize() / 2)- error)//这里需要多减去一个较小值才能准确判断，这里应该是由于double运算精度的原因
		return true;
		else
			return false;
	}
	virtual void Show(CDC* pDC)
	{
		pDC->Ellipse(int(m_x - m_nSize / 2), int(m_y - m_nSize / 2), int(m_x + m_nSize / 2), int(m_y + m_nSize / 2));
	}
	virtual void SetImg(CImage* pImg) { m_pImg = pImg; }

	~MyPoint() {};
protected:
	double m_x = 0;
	double m_y = 0;
	double m_nSize = 50;//如果要改变nSize，至少改变两处才能满足碰撞检测条件，dStep与MyPoint构造函数中i*nSize
	CImage* m_pImg = nullptr;
};

