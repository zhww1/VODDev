
// VODClientView.cpp : CVODClientView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "VODClient.h"
#endif

#include "VODClientDoc.h"
#include "VODClientView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CVODClientView

IMPLEMENT_DYNCREATE(CVODClientView, CFormView)

BEGIN_MESSAGE_MAP(CVODClientView, CFormView)
	ON_WM_SIZE()
END_MESSAGE_MAP()

// CVODClientView 构造/析构

CVODClientView::CVODClientView()
	: CFormView(CVODClientView::IDD)
{
	// TODO:  在此处添加构造代码

}

CVODClientView::~CVODClientView()
{
}

void CVODClientView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MEDIA_PLAYER, m_wndPlayer);
}

BOOL CVODClientView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CFormView::PreCreateWindow(cs);
}

void CVODClientView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

}


// CVODClientView 诊断

#ifdef _DEBUG
void CVODClientView::AssertValid() const
{
	CFormView::AssertValid();
}

void CVODClientView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CVODClientDoc* CVODClientView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CVODClientDoc)));
	return (CVODClientDoc*)m_pDocument;
}
#endif //_DEBUG
// CVODClientView 消息处理程序
void CVODClientView::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	// TODO:  在此处添加消息处理程序代码

	// TODO: Add your message handler code here
	CRect rcClient;
	/*GetClientRect(&rcClient);
	if (m_wndPlayer.GetSafeHwnd())
	{
		m_wndPlayer.MoveWindow(0, 0, rcClient.Width(), rcClient.Height());
	}*/
}
BEGIN_EVENTSINK_MAP(CVODClientView, CFormView)
	ON_EVENT(CVODClientView, IDC_MEDIA_PLAYER, 6506, CVODClientView::OnDoubleclickMediaPlayer, VTS_I2 VTS_I2 VTS_I4 VTS_I4)
END_EVENTSINK_MAP()

#include "MainFrm.h"
void CVODClientView::OnDoubleclickMediaPlayer(short nButton, short nShiftState, long fX, long fY)
{
	// TODO:  在此处添加消息处理程序代码
	// TODO: Add your control notification handler code here
	CMainFrame *pFrame = (CMainFrame*)GetParentFrame();
	pFrame->ShowControlBar(&pFrame->m_LeftCtrBar,
		!pFrame->m_LeftCtrBar.IsVisible(), FALSE);
}
