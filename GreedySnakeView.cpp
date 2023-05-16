
// GreedySnakeView.cpp: CGreedySnakeView 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "GreedySnake.h"
#endif

#include "GreedySnakeDoc.h"
#include "GreedySnakeView.h"
#include"MySnake.h"

const int TIMER_SHOW_ID = 101;
const int TIMER_POSITION_UPDATE = 102;
const int TIMER_CREATE_FOOD = 103;
const int TIMER_LOSIING_LIFE = 104;
const int TIMER_ADDAUTOSNAKE = 105;
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGreedySnakeView

IMPLEMENT_DYNCREATE(CGreedySnakeView, CView)

BEGIN_MESSAGE_MAP(CGreedySnakeView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CGreedySnakeView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

// CGreedySnakeView 构造/析构

CGreedySnakeView::CGreedySnakeView() noexcept
{
	// TODO: 在此处添加构造代码

}

CGreedySnakeView::~CGreedySnakeView()
{
}

BOOL CGreedySnakeView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CGreedySnakeView 绘图

void CGreedySnakeView::OnDraw(CDC* pDC)
{
	CGreedySnakeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	// TODO: 在此处为本机数据添加绘制代码

}


// CGreedySnakeView 打印


void CGreedySnakeView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CGreedySnakeView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CGreedySnakeView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CGreedySnakeView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CGreedySnakeView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CGreedySnakeView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CGreedySnakeView 诊断

#ifdef _DEBUG
void CGreedySnakeView::AssertValid() const
{
	CView::AssertValid();
}

void CGreedySnakeView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGreedySnakeDoc* CGreedySnakeView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGreedySnakeDoc)));
	return (CGreedySnakeDoc*)m_pDocument;
}
#endif //_DEBUG


// CGreedySnakeView 消息处理程序


void CGreedySnakeView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类

	TCHAR cFilePath[1024];
	GetModuleFileName(NULL, cFilePath, 1024);
	CString str_backgound(cFilePath);
	CString str_shell(cFilePath);
	CString str_food(cFilePath);
	//CString str_snake(cFilePath);
	CString str_stone(cFilePath);
	str_backgound = str_backgound.Left(str_backgound.ReverseFind('\\') + 1) + _T("data\\background.png");
	str_shell= str_shell.Left(str_shell.ReverseFind('\\') + 1) + _T("data\\star.png");
	str_stone= str_stone.Left(str_stone.ReverseFind('\\') + 1) + _T("data\\stone.png");
	BackGroundImage.Load(str_backgound);
	ShellImage.Load(str_shell);
	//FoodImage.Load(str_food);
	StoneImage.Load(str_stone);
	//SnakeImage.Load(str_snake);
	for (auto& pt : st.stone)
	{
		pt.SetImg(&StoneImage);
	}
	
	sk.InitSnake();
	auto_sk.InitSnake();
	auto_sk.SetStatus(false);
	//auto_sk.SetSize(30);
	SetTimer(TIMER_SHOW_ID, 100, NULL);
	SetTimer(TIMER_POSITION_UPDATE, 50, NULL);
	SetTimer(TIMER_CREATE_FOOD, 1000, NULL);
	SetTimer(TIMER_LOSIING_LIFE, 1000, NULL);
	SetTimer(TIMER_ADDAUTOSNAKE, 2000, NULL);
}


void CGreedySnakeView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_mousePos.Setx(point.x);
	m_mousePos.Sety(point.y);
	CView::OnMouseMove(nFlags, point);
}


void CGreedySnakeView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	auto iter = vec_sh.begin();
	int shell_num = vec_sh.size();
	int delete_num = 0;
	std::vector<std::vector<Shell>::iterator> delete_shell;
	
	MyPoint new_food;
	MyPoint NearFood;

	switch (nIDEvent)
	{
	case TIMER_SHOW_ID:
		for (auto& shell : vec_sh)
		{
			shell.UpdatePos(sk);
			Invalidate();
		}

		//删除子弹
		while (iter != vec_sh.end())
		{
			if ((*iter).HitStone(st))
			{
				delete_shell.push_back(iter);
				
			}
			/*else if ((*iter).HitFood(fd))
			{
				delete_shell.push_back(iter);
			}*/
			iter++;
		}
		delete_num = delete_shell.size();
		for (int i = delete_num-1; i>=0; i--)//这里必须倒着删，数组顺序才不会错乱
		{
			vec_sh.erase(delete_shell[i]);
		}
		delete_shell.clear();
		
		//删除子弹
		Invalidate(TRUE);
		break;
	case TIMER_POSITION_UPDATE:
		
		if (sk.HitItself())
			Beep(1000, 100);
		if (auto_sk.HitStone(st))
		{
			for (auto& pt : auto_sk.snake)
			{
				fd.food.emplace_back(pt);
			}
			auto_sk.snake.clear();//删除蛇
			
			
		}
		if (!auto_sk.snake.empty())
		{
			for (auto& pt : sk.snake)
			{
				if (auto_sk.snake.back() && pt)
				{
					for (auto& pt : auto_sk.snake)
					{
						fd.food.emplace_back(pt);
					}
					auto_sk.snake.clear();
					break;

				}
			}
		}
		if(sk.HitStone(st))
			Beep(1000, 100);
		if(sk.snake.size()<=1)
			Beep(1000, 100);
		sk.pMoveTo(m_mousePos);

		if (!auto_sk.snake.empty())
		{
			NearFood = auto_sk.AutoFindFood(fd);
			auto_sk.pMoveTo(NearFood);
		}
		sk.EatFood(fd);
	
		
		break;
	case TIMER_CREATE_FOOD:
		new_food.Setx(rand() % SCREEN_CX);
		new_food.Sety(rand() % SCREEN_CY);
		new_food.SetImg(&FoodImage);
		fd.food.push_back(new_food);
		break;
	case TIMER_LOSIING_LIFE:
		if(sk.snake.size()>1)
		sk.snake.pop_front();
		break;
	case TIMER_ADDAUTOSNAKE:
		if(auto_sk.snake.empty())
		auto_sk.snake.emplace_back(rand() % 2462, rand() % 1378);
		break;
	default:
		break;
	}
	CView::OnTimer(nIDEvent);
}


void CGreedySnakeView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	Shell shell = sk.Fire();
	shell.SetImg(&ShellImage);
	vec_sh.push_back(shell);
	Invalidate();
	CView::OnLButtonDown(nFlags, point);
}


BOOL CGreedySnakeView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CRect rc;
	CDC dcMem;
	GetClientRect(&rc);
	CBitmap bmp; //内存中承载临时图象的位图
	dcMem.CreateCompatibleDC(pDC); //依附窗口DC创建兼容内存DC
	bmp.CreateCompatibleBitmap(pDC, rc.Width(), rc.Height());
	//创建兼容位图(必须用pDC创建，否则画出的图形变成黑色)
	CBitmap* pOldBit = dcMem.SelectObject(&bmp);
	dcMem.FillSolidRect(rc, RGB(255, 255, 255));
	//按原来背景填充客户区，不然会是黑色
	//画图，添加你要画图的代码，不过用dcMem画，而不是pDC；

	
	if (!BackGroundImage.IsNull())
	{
		BackGroundImage.Draw(dcMem, 0, 0, rc.Width(), rc.Height());
	}
	sk.Show(&dcMem);


	auto_sk.Show(&dcMem);//机器蛇自动寻路


	

	
	//st.Show(&dcMem);

	fd.Show(&dcMem);
	for (auto& pt : vec_sh)
	{
		pt.Show(&dcMem);
	}
	st.Show(&dcMem);
	pDC->BitBlt(0, 0, rc.Width(), rc.Height(), &dcMem, 0, 0, SRCCOPY);
	//将内存DC上的图象拷贝到前台

	//绘图完成后的清理
	dcMem.DeleteDC(); //删除DC

	bmp.DeleteObject(); //删除位图
	return TRUE;
	//return CView::OnEraseBkgnd(pDC);
}
