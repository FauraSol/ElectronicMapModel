
// HustMapView.cpp: CHustMapView 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "HustMap.h"
#endif
#include"MainFrm.h"
#include "HustMapDoc.h"
#include "HustMapView.h"
#include"CMapDialog.h"
#include"CMapModel.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CHustMapView

IMPLEMENT_DYNCREATE(CHustMapView, CView)

BEGIN_MESSAGE_MAP(CHustMapView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CHustMapView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_DATA_POSITION, &CHustMapView::OnDataPosition)
	ON_COMMAND(ID_DATA_ORG, &CHustMapView::OnDataOrg)
	ON_COMMAND(ID_DATA_DISTANCE, &CHustMapView::OnDataDistance)
END_MESSAGE_MAP()

// CHustMapView 构造/析构

CHustMapView::CHustMapView() noexcept
{
	// TODO: 在此处添加构造代码
}

CHustMapView::~CHustMapView()
{
}

BOOL CHustMapView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CHustMapView 绘图

void CHustMapView::OnDraw(CDC* pDC)
{
	CHustMapDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	if (pDoc->m_MapModel.GetMapFilePath() != _T(""))
	{
		//MessageBox(_T("更新视图"));
		//HBITMAP为图片句柄
		HBITMAP hBit;
		hBit = (HBITMAP)LoadImage(NULL, pDoc->m_MapModel.GetMapFilePath(),
			IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);//载入图像
		//CBitmap是对HBITMAP封装的类
		CBitmap cBit;
		//Attach()函数是CBitmap类的成员函数，作用就是将HBITMAP类型转换成CBitmap类型
		cBit.Attach(hBit);
		//创建与当前设备描述表相适应的内存DC
		CDC MemDC;
		MemDC.CreateCompatibleDC(pDC);

		BITMAP bitmap;
		cBit.GetBitmap(&bitmap);
		CBitmap* oldBit;
		//将位图选入到内存DC中，并返回旧的位图
		oldBit = MemDC.SelectObject(&cBit);

		CRect rect;
		GetClientRect(&rect);//用于获取绘图的客户区域
		//画出BITMAP位图
		pDC->StretchBlt(0, 0, rect.Width(), rect.Height(), &MemDC, 0, 0, bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);
		
	}

	// TODO: 在此处为本机数据添加绘制代码
}


// CHustMapView 打印


void CHustMapView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CHustMapView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CHustMapView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CHustMapView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CHustMapView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	//OnContextMenu(this, point);

	CMapDialog dlg;

	int ret = dlg.DoModal();
	CMainFrame* pMainFrm = (CMainFrame*)AfxGetMainWnd();//获取主窗口
	if (ret == IDOK) {
		pMainFrm->GetOutputWnd()->setBuildWindowContents(_T("点击了对话框的确定按钮"));
	}
	else if (ret == IDCANCEL) {
		pMainFrm->GetOutputWnd()->setBuildWindowContents(_T("点击了对话框的取消按钮"));
	}

}

void CHustMapView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CHustMapView 诊断

#ifdef _DEBUG
void CHustMapView::AssertValid() const
{
	CView::AssertValid();
}

void CHustMapView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CHustMapDoc* CHustMapView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CHustMapDoc)));
	return (CHustMapDoc*)m_pDocument;
}
#endif //_DEBUG


// CHustMapView 消息处理程序

void CHustMapView::OnLButtonDown(UINT nFlags, CPoint point) {
	LONG xpos = point.x;//获取点击的x
	LONG ypos = point.y;//获取点击的y
	CString posInfo;
	posInfo.Format(_T("鼠标点击位置：(%d,%d)"), xpos, ypos);

	CMainFrame* pMainFrm = (CMainFrame*)AfxGetMainWnd();//获取主窗口
	pMainFrm->GetOutputWnd()->setBuildWindowContents(posInfo);

	DrawCircle(point, 5);

	//存储鼠标点击时的坐标
	this->m_LineStart = point;

	CView::OnLButtonDown(nFlags, point);
}

void CHustMapView::DrawCircle(CPoint center, LONG radius) {
	//CDC是MFC封装的Windows绘图设备的一个类，用于绘图
	//CClientDC是CDC的派生类，只能在窗口的客户区绘图
	//构造的时候用GetDC，析构用ReleaseDC
	//CClientDC的构造函数需要一个参数，这个参数是绘图窗口的指针，使用this

	CClientDC dc(this);
	CBrush brush, * oldbrush;
	brush.CreateSolidBrush(RGB(0xFF, 0x00, 0x00));
	oldbrush = dc.SelectObject(&brush);
	dc.Ellipse(center.x - radius, center.y - radius, center.x + radius, center.y + radius);
	dc.SelectObject(oldbrush);

}

void CHustMapView::DrawLine(CPoint start, CPoint end) {
	CClientDC dc(this);
	CPen pen(PS_SOLID, 3, RGB(0xFF, 0x00, 0x00));
	CPen* oldPen;
	oldPen = dc.SelectObject(&pen);
	dc.MoveTo(start.x, start.y);
	dc.LineTo(end.x, end.y);
	dc.SelectObject(oldPen);
}


void CHustMapView::OnLButtonUp(UINT nFlags, CPoint point)
{
	this->DrawLine(this->m_LineStart, point);

	this->m_DraggingState = false;

	CView::OnLButtonUp(nFlags, point);
}


void CHustMapView::OnMouseMove(UINT nFlags, CPoint point)
{
	if (nFlags & MK_LBUTTON) {
		if (this->m_DraggingState) {
			this->DrawRubberLine(this->m_LineStart, this->m_LastLineEnd);
		}
		this->DrawRubberLine(this->m_LineStart, point);
		this->m_LastLineEnd = point;
		this->m_DraggingState = true;
	}

	CView::OnMouseMove(nFlags, point);
}

void CHustMapView::DrawRubberLine(CPoint start, CPoint end) {
	CClientDC dc(this);
	dc.SetROP2(R2_NOTXORPEN);
	CPen pen(PS_SOLID, 3, RGB(0xFF, 0x00, 0x00));
	CPen* oldPen;
	oldPen = dc.SelectObject(&pen);
	dc.MoveTo(start.x, start.y);
	dc.LineTo(end.x, end.y);
	dc.SelectObject(oldPen);
}

static CMapModel tmp;

void CHustMapView::OnDataPosition()
{

	tmp.setLocInfo();
	for (int i = 1; i <= 25; i++) {
		DrawCircle(tmp.LocInfo[i].position, 5);
	}
	
}


void CHustMapView::OnDataOrg()
{
	tmp.setOrgInfo();
	
}




void CHustMapView::OnDataDistance()
{
	tmp.setDisInfo();
	
}
