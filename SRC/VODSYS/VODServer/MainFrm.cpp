
// MainFrm.cpp : CMainFrame ���ʵ��
//

#include "stdafx.h"
#include "VODServer.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
CMainFrame * g_pWnd;
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_COMMAND(ID_TOOLBAR_NAVIGATE, &CMainFrame::OnToolbarNavigate)
	ON_UPDATE_COMMAND_UI(ID_TOOLBAR_NAVIGATE, &CMainFrame::OnUpdateToolbarNavigate)
	ON_COMMAND(ID_TOOLBAR_EDIT, &CMainFrame::OnToolbarEdit)
	ON_UPDATE_COMMAND_UI(ID_TOOLBAR_EDIT, &CMainFrame::OnUpdateToolbarEdit)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // ״̬��ָʾ��
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame ����/����

CMainFrame::CMainFrame()
{
	// TODO:  �ڴ���ӳ�Ա��ʼ������
	//�������ݿ� 
	BOOL bRet = m_adoConnection.ConnectAccess("../../../DB/VODDB.mdb");
	if (!bRet)
	{
		MessageBox(_T("�������ݿ�ʧ�ܣ�"));
	
	}
	//m_bSvrStart = TRUE;
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("δ�ܴ���������\n");
		return -1;      // δ�ܴ���
	}

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("δ�ܴ���״̬��\n");
		return -1;      // δ�ܴ���
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	// TODO:  �������Ҫ��ͣ������������ɾ��������
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);




	//�������Ĵ�����ͣ��
	if (!m_LeftCtrBar.Create(_T("����������"), this, CSize(230, 260), TRUE, 123))
	{
		TRACE0("Failed to create mybar\n");
		return -1;
	}
	if (!m_BottomCtrBar.Create(_T("�༭������"), this, CSize(200, 170), TRUE, 124))
	{
		TRACE0("Failed to create mybar\n");
		return -1;
	}
	m_LeftCtrBar.SetBarStyle(m_LeftCtrBar.GetBarStyle() | CBRS_TOOLTIPS
		| CBRS_FLYBY | CBRS_SIZE_DYNAMIC);
	m_BottomCtrBar.SetBarStyle(m_BottomCtrBar.GetBarStyle() | CBRS_TOOLTIPS
		| CBRS_FLYBY | CBRS_SIZE_DYNAMIC);
	m_LeftCtrBar.EnableDocking(CBRS_ALIGN_ANY);
	m_BottomCtrBar.EnableDocking(CBRS_ALIGN_ANY);

	DockControlBar(&m_BottomCtrBar, AFX_IDW_DOCKBAR_BOTTOM);  //ͣ���ڵײ� 
	DockControlBar(&m_LeftCtrBar, AFX_IDW_DOCKBAR_LEFT);      //ͣ�������


	//���ù�������ť���ı���ϵͳ�������� 
	m_wndToolBar.SetButtonText(0, _T(" ���͵��� "));
	m_wndToolBar.SetButtonText(1, _T(" ��Ƶ�༭ "));
	//������������ť�Ĵ�С�������ı���ʾ�����������������ı��ĵ�����������
	/////////////����������/////////////////
	CRect rc(0, 0, 0, 0);
	CSize sizeMax(0, 0);
	CToolBarCtrl& bar = m_wndToolBar.GetToolBarCtrl();
	for (int nIndex = bar.GetButtonCount() - 1; nIndex >= 0; nIndex--)
	{
		bar.GetItemRect(nIndex, rc);

		rc.NormalizeRect();
		sizeMax.cx = __max(rc.Size().cx, sizeMax.cx);
		sizeMax.cy = __max(rc.Size().cy, sizeMax.cy);
	}
	//sizeMax.cx += 10;
	m_wndToolBar.SetSizes(sizeMax, CSize(20, 18));
	//���ؼ��Ĵ���
	if (!m_wndTree.Create((WS_CHILD | WS_VISIBLE | TVS_HASLINES | TVS_HASBUTTONS | TVS_LINESATROOT), CRect(0, 0, 0, 0), &m_LeftCtrBar, 100))
	{
		TRACE0(_T("Failed to create instant bar child\n"));
		return -1;
	}
	//�������ؼ��ķ�� 
	m_wndTree.ModifyStyleEx(0, WS_EX_CLIENTEDGE);
	//�������ؼ�����ɫ ����һ����û�� 
	//m_wndTree.SetBkColor(RGB(255, 0, 0)); //PeachPuff
	//�Ի��� (�ײ��Ի��򴴽���ʾ �ʹ����ݿ��м�����Ͽ��������Ƶ���� )
	if (!m_dlgVideo.Create(IDD_DLG_VIDEO, &m_BottomCtrBar))
	{
		return -1;
	}
	m_dlgVideo.ShowWindow(SW_SHOW);
	m_dlgVideo.InitVideoTypeCtrl();

	//��������ؼ�������Ƶ���� ����Ҳ�Ѿ��������ؼ��� 
	InitTypeTreeCtrl();
	//����������
	m_NetServer.InitServer();
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO:  �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return TRUE;
}

// CMainFrame ���

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame ��Ϣ�������



void CMainFrame::OnToolbarNavigate()
{
	// TODO:  �ڴ���������������

	// TODO: Add your command handler code here
	ShowControlBar(&m_LeftCtrBar, !m_LeftCtrBar.IsVisible(), FALSE);


}


void CMainFrame::OnUpdateToolbarNavigate(CCmdUI *pCmdUI)
{
	// TODO:  �ڴ������������û����洦��������

	// TODO: Add your command update UI handler code here

	pCmdUI->SetCheck(m_LeftCtrBar.IsVisible());
}


void CMainFrame::OnToolbarEdit()
{
	// TODO:  �ڴ���������������
	// TODO: Add your command handler code here
	ShowControlBar(&m_BottomCtrBar, !m_BottomCtrBar.IsVisible(), FALSE);
}
void CMainFrame::OnUpdateToolbarEdit(CCmdUI *pCmdUI)
{
	// TODO:  �ڴ������������û����洦��������
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_BottomCtrBar.IsVisible());
}

#include "TypeManager.h"
void CMainFrame::InitTypeTreeCtrl()
{
	//���������Ƶ������Ķ���
	CTypeManager typeMgr(&m_adoConnection);
	CList<CType, CType> lstTypes;
	//��ȡ��Ƶ���͵���Ϣ���浽����  lstTypes��
	typeMgr.GetAllType(&lstTypes);
	CType type;
	//�������ؼ��ĸ��ڵ�
	HTREEITEM hRoot = m_wndTree.InsertItem(_T("��������"));
	for (int i = 0; i<lstTypes.GetCount(); i++)
	{
		//�������л�ȡ��Ƶ���͵�����
		type = lstTypes.GetAt(lstTypes.FindIndex(i));
		//����Ƶ������Ϊ���ڵ����Ʋ��뵽���ؼ�
		HTREEITEM hItem = m_wndTree.InsertItem(type.strTypeName, hRoot);
		//����Ƶ����ID������Ϊ�ڵ�ĸ�������
		m_wndTree.SetItemData(hItem, type.nTypeID);
	}
	//�������ڵ�߶�
	m_wndTree.SetItemHeight(20);
	//�ڸ��ڵ�չ�����ؼ�
	m_wndTree.Expand(hRoot, TVE_EXPAND);
}
