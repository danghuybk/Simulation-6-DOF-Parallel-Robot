
// parallel_robotView.h : interface of the CparallelrobotView class
//

#pragma once
#include"robotcontrolview.h"

class CparallelrobotView : public CView
{
protected: // create from serialization only
	CparallelrobotView() noexcept;
	DECLARE_DYNCREATE(CparallelrobotView)

// Attributes
public:
	CparallelrobotDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CparallelrobotView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()

	// phuong thuc va thuoc tinh do nguoi dung dat
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);

	robotcontrolview     robotcontrol_view;
	BOOL Is_loaddata = FALSE;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};

#ifndef _DEBUG  // debug version in parallel_robotView.cpp
inline CparallelrobotDoc* CparallelrobotView::GetDocument() const
   { return reinterpret_cast<CparallelrobotDoc*>(m_pDocument); }
#endif

