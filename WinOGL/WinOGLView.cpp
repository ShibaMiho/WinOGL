
// WinOGLView.cpp : CWinOGLView クラスの実装
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS は、プレビュー、縮小版、および検索フィルター ハンドラーを実装している ATL プロジェクトで定義でき、
// そのプロジェクトとのドキュメント コードの共有を可能にします。
#ifndef SHARED_HANDLERS
#include "WinOGL.h"
#endif

#include "WinOGLDoc.h"
#include "WinOGLView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CWinOGLView

IMPLEMENT_DYNCREATE(CWinOGLView, CView)

BEGIN_MESSAGE_MAP(CWinOGLView, CView)
	ON_WM_LBUTTONDOWN()
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
	ON_COMMAND(ID_XYZ, &CWinOGLView::OnXyz)
	ON_COMMAND(ID_EDIT_MODE, &CWinOGLView::OnEditMode)
	ON_COMMAND(ID_CREATE_MODE, &CWinOGLView::OnCreateMode)
	ON_COMMAND(ID_SURFACE_MODE, &CWinOGLView::OnSurfaceMode)
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_RBUTTONUP()
	ON_WM_MOUSEWHEEL()
	ON_UPDATE_COMMAND_UI(ID_XYZ, &CWinOGLView::OnUpdateXyz)
	ON_UPDATE_COMMAND_UI(ID_CREATE_MODE, &CWinOGLView::OnUpdateCreateMode)
	ON_UPDATE_COMMAND_UI(ID_EDIT_MODE, &CWinOGLView::OnUpdateEditMode)
	ON_UPDATE_COMMAND_UI(ID_SURFACE_MODE, &CWinOGLView::OnUpdateSurfaceMode)
	ON_COMMAND(ID_DELETE_MODE, &CWinOGLView::OnDeleteMode)
	ON_UPDATE_COMMAND_UI(ID_DELETE_MODE, &CWinOGLView::OnUpdateDeleteMode)
	ON_COMMAND(ID_VIEW_MODE, &CWinOGLView::OnViewMode)
	ON_UPDATE_COMMAND_UI(ID_VIEW_MODE, &CWinOGLView::OnUpdateViewMode)
	ON_WM_KEYDOWN()
	ON_COMMAND(ID_VIEW_MODE_IDOU, &CWinOGLView::OnViewModeIdou)
	ON_COMMAND(ID_VIEW_MODE_KAITEN, &CWinOGLView::OnViewModeKaiten)
	ON_COMMAND(ID_VIEW_MODE_KAKUDAI, &CWinOGLView::OnViewModeKakudai)
	ON_COMMAND(ID_VIEW_MODE_SYUKUSYOU, &CWinOGLView::OnViewModeSyukusyou)
	ON_UPDATE_COMMAND_UI(ID_VIEW_MODE_IDOU, &CWinOGLView::OnUpdateViewModeIdou)
	ON_UPDATE_COMMAND_UI(ID_VIEW_MODE_KAITEN, &CWinOGLView::OnUpdateViewModeKaiten)
	ON_UPDATE_COMMAND_UI(ID_VIEW_MODE_KAKUDAI, &CWinOGLView::OnUpdateViewModeKakudai)
	ON_UPDATE_COMMAND_UI(ID_VIEW_MODE_SYUKUSYOU, &CWinOGLView::OnUpdateViewModeSyukusyou)
	ON_COMMAND(ID_3VIEW_MODE, &CWinOGLView::On3viewMode)
	ON_UPDATE_COMMAND_UI(ID_3VIEW_MODE, &CWinOGLView::OnUpdate3viewMode)
	ON_COMMAND(ID_VIEW_LIGHT, &CWinOGLView::OnViewLight)
	ON_UPDATE_COMMAND_UI(ID_VIEW_LIGHT, &CWinOGLView::OnUpdateViewLight)
END_MESSAGE_MAP()

// CWinOGLView コンストラクション/デストラクション

CWinOGLView::CWinOGLView() noexcept
{
	// TODO: 構築コードをここに追加します。

}

CWinOGLView::~CWinOGLView()
{
}

BOOL CWinOGLView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: この位置で CREATESTRUCT cs を修正して Window クラスまたはスタイルを
	//  修正してください。

	return CView::PreCreateWindow(cs);
}

// CWinOGLView 描画

void CWinOGLView::OnDraw(CDC* pDC)
{
	CWinOGLDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	wglMakeCurrent(pDC->m_hDC, m_hRC);

	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	AC.Draw();

	glFlush();
	SwapBuffers(pDC->m_hDC);

	wglMakeCurrent(pDC->m_hDC, NULL);

}


// CWinOGLView の診断

#ifdef _DEBUG
void CWinOGLView::AssertValid() const
{
	CView::AssertValid();
}

void CWinOGLView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CWinOGLDoc* CWinOGLView::GetDocument() const // デバッグ以外のバージョンはインラインです。
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CWinOGLDoc)));
	return (CWinOGLDoc*)m_pDocument;
}
#endif //_DEBUG


// CWinOGLView メッセージ ハンドラー


void CWinOGLView::OnLButtonDown(UINT nFlags, CPoint point)
{
	AC.SetLButtonDownFlag(true);

	CRect rect;
	GetClientRect(rect);

	double X;
	double Y;
	X = (double)point.x / rect.Width();		//正規化座標系変換
	Y = 1.0-(double)point.y / rect.Height();//正規化座標系変換

	X = (X - 0.5) * 2;
	Y = (Y - 0.5) * 2;

	double hi;
	if (rect.Width() > rect.Height())
	{
		hi = (double)rect.Width() / rect.Height();
		X = X * hi;
	}
	else {
		hi = (double)rect.Height() / rect.Width();
		Y = Y * hi;
	}

	AC.LButtonDownSwitch(X, Y);
	AC.SaveBeforeShape();

	RedrawWindow();
	CView::OnLButtonDown(nFlags, point);
}

void CWinOGLView::OnLButtonUp(UINT nFlags, CPoint point)
{
	AC.SetLButtonDownFlag(false);

	CRect rect;
	GetClientRect(rect);

	double X;
	double Y;
	X = (double)point.x / rect.Width();		//正規化座標系変換
	Y = 1.0 - (double)point.y / rect.Height();//正規化座標系変換

	X = (X - 0.5) * 2;
	Y = (Y - 0.5) * 2;

	double hi;
	if (rect.Width() > rect.Height())
	{
		hi = (double)rect.Width() / rect.Height();
		X = X * hi;
	}
	else {
		hi = (double)rect.Height() / rect.Width();
		Y = Y * hi;
	}

	AC.LButtonUpSwitch(X,Y);

	RedrawWindow();
	CView::OnLButtonUp(nFlags, point);
	
}

void CWinOGLView::OnMouseMove(UINT nFlags, CPoint point)
{
	if (AC.GetLButtonDownFlag() == true) {
		CRect rect;
		GetClientRect(rect);
		double X;
		double Y;
		X = (double)point.x / rect.Width();		//正規化座標系変換
		Y = 1.0 - (double)point.y / rect.Height();//正規化座標系変換

		X = (X - 0.5) * 2;
		Y = (Y - 0.5) * 2;

		double hi;
		if (rect.Width() > rect.Height())
		{
			hi = (double)rect.Width() / rect.Height();
			X = X * hi;
		}
		else {
			hi = (double)rect.Height() / rect.Width();
			Y = Y * hi;
		}

		AC.MouseMoveSwitch(X, Y);

		RedrawWindow();
		CView::OnMouseMove(nFlags, point);
	}
}

void CWinOGLView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	CRect rect;
	GetClientRect(rect);

	double X;
	double Y;
	X = (double)point.x / rect.Width();			//正規化座標系変換
	Y = 1.0 - (double)point.y / rect.Height();	//正規化座標系変換

	X = (X - 0.5) * 2;
	Y = (Y - 0.5) * 2;

	double hi;
	if (rect.Width() > rect.Height())
	{
		hi = (double)rect.Width() / rect.Height();
		X = X * hi;
	}
	else {
		hi = (double)rect.Height() / rect.Width();
		Y = Y * hi;
	}

	AC.LButtonDblClkSwitch(X, Y);

	RedrawWindow();
	CView::OnLButtonDblClk(nFlags, point);
}

void CWinOGLView::OnRButtonDown(UINT nFlags, CPoint point)
{
	AC.SetRButtonDownFlag(true);

	CRect rect;
	GetClientRect(rect);

	double X;
	double Y;
	X = (double)point.x / rect.Width();			//正規化座標系変換
	Y = 1.0 - (double)point.y / rect.Height();	//正規化座標系変換

	X = (X - 0.5) * 2;
	Y = (Y - 0.5) * 2;

	double hi;
	if (rect.Width() > rect.Height())
	{
		hi = (double)rect.Width() / rect.Height();
		X = X * hi;
	}
	else {
		hi = (double)rect.Height() / rect.Width();
		Y = Y * hi;
	}

	AC.RButtonDownSwitch(X, Y);

	RedrawWindow();
	CView::OnRButtonDown(nFlags, point);
}

void CWinOGLView::OnRButtonUp(UINT nFlags, CPoint point)
{
	AC.SetRButtonDownFlag(false);

	CRect rect;
	GetClientRect(rect);

	double X;
	double Y;
	X = (double)point.x / rect.Width();		//正規化座標系変換
	Y = 1.0 - (double)point.y / rect.Height();//正規化座標系変換

	X = (X - 0.5) * 2;
	Y = (Y - 0.5) * 2;

	double hi;
	if (rect.Width() > rect.Height())
	{
		hi = (double)rect.Width() / rect.Height();
		X = X * hi;
	}
	else {
		hi = (double)rect.Height() / rect.Width();
		Y = Y * hi;
	}

	AC.RButtonUpSwitch(X, Y);

	RedrawWindow();
	CView::OnRButtonUp(nFlags, point);
}

BOOL CWinOGLView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	AC.SaveBeforeShape();
	AC.MouseWheelSwitch(zDelta);

	RedrawWindow();
	return CView::OnMouseWheel(nFlags, zDelta, pt);
}

void CWinOGLView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	AC.KeyDownSwitch(nChar);
	RedrawWindow();
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


int CWinOGLView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW |
		PFD_SUPPORT_OPENGL |
		PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,
		32,
		0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		24,
		0,0,
		PFD_MAIN_PLANE,
		0,
		0,0,0,
	};
	CClientDC clientDC(this);
	int pixelFormat = ChoosePixelFormat(clientDC.m_hDC, &pfd);
	SetPixelFormat(clientDC.m_hDC, pixelFormat, &pfd);
	m_hRC = wglCreateContext(clientDC.m_hDC);

	return 0;
}

void CWinOGLView::OnDestroy()
{
	CView::OnDestroy();
	wglDeleteContext(m_hRC);

}

BOOL CWinOGLView::OnEraseBkgnd(CDC* pDC)
{
	return true;
}

void CWinOGLView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);
	CClientDC clientDC(this);
	wglMakeCurrent(clientDC.m_hDC, m_hRC);

	glViewport(0, 0, cx, cy);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	double hi;

	if(cx > cy)
	{
		hi = (double)cx / cy;
		glOrtho(-1 * hi, 1 * hi, -1, 1, -100, 100);
	}
	else {
		hi = (double)cy / cx;
		glOrtho(-1, 1, -1 * hi, 1 * hi, -100, 100);
	}
	
	glMatrixMode(GL_MODELVIEW);

	RedrawWindow();
	wglMakeCurrent(clientDC.m_hDC, NULL);

}

void CWinOGLView::OnXyz()
{
	AC.ChangeAxisFlag();
	RedrawWindow();
}

void CWinOGLView::OnUpdateXyz(CCmdUI* pCmdUI)
{
	if (AC.GetAxisFlag() == true) {
		pCmdUI->SetCheck(true);
	}
	else {
		pCmdUI->SetCheck(false);
	}
}

void CWinOGLView::OnCreateMode()
{
	AC.ChangeModeCreate();
	RedrawWindow();
}

void CWinOGLView::OnUpdateCreateMode(CCmdUI* pCmdUI)
{
	if (AC.GetCreateModeFlag() == true) {
		pCmdUI->SetCheck(true);
	}
	else {
		pCmdUI->SetCheck(false);
	}
}

void CWinOGLView::OnEditMode()
{
	AC.ChangeModeEdit();
	RedrawWindow();
}

void CWinOGLView::OnUpdateEditMode(CCmdUI* pCmdUI)
{
	if (AC.GetEditModeFlag() == true) {
		pCmdUI->SetCheck(true);
	}
	else {
		pCmdUI->SetCheck(false);
	}
}

void CWinOGLView::OnSurfaceMode()
{
	AC.ChangePolygonFlag();
	RedrawWindow();
}

void CWinOGLView::OnUpdateSurfaceMode(CCmdUI* pCmdUI)
{
	if (AC.GetPolygonFlag() == true) {
		pCmdUI->SetCheck(true);
	}
	else {
		pCmdUI->SetCheck(false);
	}
}

void CWinOGLView::OnDeleteMode()
{
	AC.ChangeModeDelete();
	RedrawWindow();
}

void CWinOGLView::OnUpdateDeleteMode(CCmdUI* pCmdUI)
{
	if (AC.GetDeleteModeFlag() == true) {
		pCmdUI->SetCheck(true);
	}
	else {
		pCmdUI->SetCheck(false);
	}
}


void CWinOGLView::OnViewMode()
{
	AC.ChangeModeView();
	RedrawWindow();
}

void CWinOGLView::OnUpdateViewMode(CCmdUI* pCmdUI)
{
	if (AC.GetViewModeFlag() == true) {
		pCmdUI->SetCheck(true);
	}
	else {
		pCmdUI->SetCheck(false);
	}
}

void CWinOGLView::OnViewModeIdou()
{
	AC.ChangeViewModeIdou();
	RedrawWindow();
}

void CWinOGLView::OnUpdateViewModeIdou(CCmdUI* pCmdUI)
{
	if (AC.GetViewMode() == 1) {
		pCmdUI->SetCheck(true);
	}
	else {
		pCmdUI->SetCheck(false);
	}
}

void CWinOGLView::OnViewModeKaiten()
{
	AC.ChangeViewModeKaiten();
	RedrawWindow();
}

void CWinOGLView::OnUpdateViewModeKaiten(CCmdUI* pCmdUI)
{
	if (AC.GetViewMode() == 2) {
		pCmdUI->SetCheck(true);
	}
	else {
		pCmdUI->SetCheck(false);
	}
}

void CWinOGLView::OnViewModeKakudai()
{
	AC.ChangeViewModeKakudai();
	RedrawWindow();
}

void CWinOGLView::OnUpdateViewModeKakudai(CCmdUI* pCmdUI)
{
	if (AC.GetViewMode() == 3) {
		pCmdUI->SetCheck(true);
	}
	else {
		pCmdUI->SetCheck(false);
	}
}

void CWinOGLView::OnViewModeSyukusyou()
{
	AC.ChangeViewModeSyukusyou();
	RedrawWindow();
}

void CWinOGLView::OnUpdateViewModeSyukusyou(CCmdUI* pCmdUI)
{
	if (AC.GetViewMode() == 4) {
		pCmdUI->SetCheck(true);
	}
	else {
		pCmdUI->SetCheck(false);
	}
}

void CWinOGLView::On3viewMode()
{
	AC.ChangeView3DFlag();
	RedrawWindow();
}

void CWinOGLView::OnUpdate3viewMode(CCmdUI* pCmdUI)
{
	if (AC.GetView3DFlag() == true) {
		pCmdUI->SetCheck(true);
	}
	else {
		pCmdUI->SetCheck(false);
	}
}

void CWinOGLView::OnViewLight()
{
	AC.ChangeViewLightFlag();
	RedrawWindow();
}

void CWinOGLView::OnUpdateViewLight(CCmdUI* pCmdUI)
{
	if (AC.GetViewLightFlag() == true) {
		pCmdUI->SetCheck(true);
	}
	else {
		pCmdUI->SetCheck(false);
	}
}
