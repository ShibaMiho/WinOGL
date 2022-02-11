
// WinOGLView.h : CWinOGLView クラスのインターフェイス
//

#pragma once
#include<gl/GL.h>
#include "AdminControl.h"

class CWinOGLView : public CView
{
protected: // シリアル化からのみ作成します。
	CWinOGLView() noexcept;
	DECLARE_DYNCREATE(CWinOGLView)

// 属性
public:
	CWinOGLDoc* GetDocument() const;

// 操作
public:

// オーバーライド
public:
	virtual void OnDraw(CDC* pDC);  // このビューを描画するためにオーバーライドされます。
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// 実装
public:
	virtual ~CWinOGLView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成された、メッセージ割り当て関数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);

private:
	HGLRC m_hRC;
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSize(UINT nType, int cx, int cy);
private:
	CAdminControl AC;
public:
	afx_msg void OnXyz();
	afx_msg void OnEditMode();
	afx_msg void OnCreateMode();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnShapemoveMode();
//	afx_msg void OnMouseHWheel(UINT nFlags, short zDelta, CPoint pt);
//	afx_msg void OnMouseHWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnUpdateXyz(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCreateMode(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditMode(CCmdUI* pCmdUI);
//	afx_msg void OnSurface();
	afx_msg void OnSurfaceMode();
	afx_msg void OnUpdateSurfaceMode(CCmdUI* pCmdUI);
	afx_msg void OnDeleteMode();
	afx_msg void OnUpdateDeleteMode(CCmdUI* pCmdUI);
	afx_msg void OnViewMode();
	afx_msg void OnUpdateViewMode(CCmdUI* pCmdUI);
//	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
//	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnViewModeIdou();
	afx_msg void OnViewModeKaiten();
	afx_msg void OnViewModeKakudai();
	afx_msg void OnViewModeSyukusyou();
	afx_msg void OnUpdateViewModeIdou(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewModeKaiten(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewModeKakudai(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewModeSyukusyou(CCmdUI* pCmdUI);
	afx_msg void On3viewMode();
	afx_msg void OnUpdate3viewMode(CCmdUI* pCmdUI);
	afx_msg void OnViewLight();
	afx_msg void OnUpdateViewLight(CCmdUI* pCmdUI);
};

#ifndef _DEBUG  // WinOGLView.cpp のデバッグ バージョン
inline CWinOGLDoc* CWinOGLView::GetDocument() const
   { return reinterpret_cast<CWinOGLDoc*>(m_pDocument); }
#endif

