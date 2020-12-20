
// HustMapView.h: CHustMapView 类的接口
//

#pragma once
#include "HustMapDoc.h"

class CHustMapView : public CView
{
protected: // 仅从序列化创建
	CHustMapView() noexcept;
	DECLARE_DYNCREATE(CHustMapView)
protected:
	//按下左键时的坐标点，作为画线起点
	CPoint m_LineStart;
	//上次化纤的终点
	CPoint m_LastLineEnd;
	//鼠标是否位于拖拽状态
	boolean m_DraggingState = false;

// 特性
public:
	CHustMapDoc* GetDocument() const;

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
	virtual ~CHustMapView();
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
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//根据指定的圆心和班级那个画圆
	void DrawCircle(CPoint center, LONG radius);
	//画直线，指定起点start和终点end
	void DrawLine(CPoint start, CPoint end);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//画橡皮筋线，会擦除上次的直线
	void DrawRubberLine(CPoint start, CPoint end);
	afx_msg void OnDataPosition();
	afx_msg void OnDataOrg();
	afx_msg void OnDataDistance();
};

#ifndef _DEBUG  // HustMapView.cpp 中的调试版本
inline CHustMapDoc* CHustMapView::GetDocument() const
   { return reinterpret_cast<CHustMapDoc*>(m_pDocument); }
#endif

