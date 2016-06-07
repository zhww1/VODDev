
// VODClientView.cpp : CVODClientView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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

// CVODClientView ����/����

CVODClientView::CVODClientView()
	: CFormView(CVODClientView::IDD)
{
	// TODO:  �ڴ˴���ӹ������

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
	// TODO:  �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CFormView::PreCreateWindow(cs);
}

void CVODClientView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

}


// CVODClientView ���

#ifdef _DEBUG
void CVODClientView::AssertValid() const
{
	CFormView::AssertValid();
}

void CVODClientView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CVODClientDoc* CVODClientView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CVODClientDoc)));
	return (CVODClientDoc*)m_pDocument;
}
#endif //_DEBUG
// CVODClientView ��Ϣ�������
void CVODClientView::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	// TODO:  �ڴ˴������Ϣ����������

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
	// TODO:  �ڴ˴������Ϣ����������
	// TODO: Add your control notification handler code here
	CMainFrame *pFrame = (CMainFrame*)GetParentFrame();
	pFrame->ShowControlBar(&pFrame->m_LeftCtrBar,
		!pFrame->m_LeftCtrBar.IsVisible(), FALSE);
}
