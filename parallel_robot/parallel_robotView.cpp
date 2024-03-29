
// parallel_robotView.cpp : implementation of the CparallelrobotView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "parallel_robot.h"
#endif

#include "parallel_robotDoc.h"
#include "parallel_robotView.h"
#include "OpenGL/OpenGLInit.h"
COpenGLInit openGLInit; 
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CparallelrobotView

IMPLEMENT_DYNCREATE(CparallelrobotView, CView)

BEGIN_MESSAGE_MAP(CparallelrobotView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CparallelrobotView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_CHAR()
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
	ON_WM_TIMER()
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
	ON_WM_MOUSEWHEEL()
	ON_WM_MOUSEMOVE()
	ON_WM_TIMER()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

// CparallelrobotView construction/destruction

CparallelrobotView::CparallelrobotView() noexcept
{
	// TODO: add construction code here

}

CparallelrobotView::~CparallelrobotView()
{
}

BOOL CparallelrobotView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	cs.style |= WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

	return CView::PreCreateWindow(cs);
}

// CparallelrobotView drawing

void CparallelrobotView::OnDraw(CDC* /*pDC*/)
{
	CparallelrobotDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	openGLInit.OnDraw(); // ve robot
	// TODO: add draw code for native data here
}


// CparallelrobotView printing


void CparallelrobotView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CparallelrobotView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CparallelrobotView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CparallelrobotView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CparallelrobotView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CparallelrobotView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CparallelrobotView diagnostics

#ifdef _DEBUG
void CparallelrobotView::AssertValid() const
{
	CView::AssertValid();
}

void CparallelrobotView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CparallelrobotDoc* CparallelrobotView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CparallelrobotDoc)));
	return (CparallelrobotDoc*)m_pDocument;
}
#endif //_DEBUG


// CparallelrobotView message handlers
int CparallelrobotView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{

	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	openGLInit.OnCreate(m_hWnd, this->GetDC()->m_hDC);
	openGLInit.m_Robot.m_dScale = 1;
	openGLInit.m_Robot.InitData();
	SetTimer(openGLInit.m_nTimerID, openGLInit.m_nTimerElapse, NULL);

	return 0;
}
void CparallelrobotView::OnDestroy()
{

	CView::OnDestroy();
	// TODO: Add your message handler code here
	KillTimer(openGLInit.m_nTimerID);

	openGLInit.OnDestroy();

}


void CparallelrobotView::OnSize(UINT nType, int cx, int cy)
{

	CView::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	openGLInit.OnSize(nType, cx, cy);
}





BOOL CparallelrobotView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	openGLInit.m_MayaCamera.OnMouseWheel(nFlags, zDelta, pt);


	return CView::OnMouseWheel(nFlags, zDelta, pt);
}


void CparallelrobotView::OnMouseMove(UINT nFlags, CPoint point)
{
	openGLInit.m_MayaCamera.OnMouseMove(nFlags, point);

	CView::OnMouseMove(nFlags, point);
}

void CparallelrobotView::OnTimer(UINT_PTR nIDEvent)
{
	if (Is_loaddata)
	{
		openGLInit.m_Robot.UpdateData();// update du lieu
	}
	CMainFrame* pMainFrame = afxGetMainFrame();
	if (pMainFrame)
	{
		pMainFrame->robotcontrol_view.robotcontrol_dlg.Display_data();

	}
	RedrawWindow(); // ve lai cua so

	CView::OnTimer(nIDEvent);
}


BOOL CparallelrobotView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default

	return TRUE; // ham nay dung de cua so khong bi nhap nhay do ve lien tuc pane va bkgnd
}
