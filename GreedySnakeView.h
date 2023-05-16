
// GreedySnakeView.h: CGreedySnakeView 类的接口
//

#pragma once
#include<vector>
#include"MyPoint.h"
#include"MySnake.h"
#include"Shell.h"
#include"Food.h"
#include"Stone.h"


class CGreedySnakeView : public CView
{
protected: // 仅从序列化创建
	CGreedySnakeView() noexcept;
	DECLARE_DYNCREATE(CGreedySnakeView)

// 特性
public:
	CGreedySnakeDoc* GetDocument() const;
public:
	
	MySnake sk;
	MySnake auto_sk;
	Food fd;
	MyPoint m_mousePos;
	Stone st;
	std::vector<Shell> vec_sh;
	CImage BackGroundImage, ShellImage,FoodImage,SnakeImage,StoneImage;
// 操作
public:
	
// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CGreedySnakeView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};

#ifndef _DEBUG  // GreedySnakeView.cpp 中的调试版本
inline CGreedySnakeDoc* CGreedySnakeView::GetDocument() const
   { return reinterpret_cast<CGreedySnakeDoc*>(m_pDocument); }
#endif

