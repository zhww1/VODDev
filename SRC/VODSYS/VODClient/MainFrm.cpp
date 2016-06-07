
// MainFrm.cpp : CMainFrame ���ʵ��
//

#include "stdafx.h"
#include "VODClient.h"
#include "resource.h"
#include "MainFrm.h"
#include "VODClientView.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_NOTIFY(TVN_SELCHANGED, 100, OnSelchangedTree)  //���100Ҫ���ݶ�̬�������ؼ���ID  ��100
	ON_NOTIFY(NM_DBLCLK, 100, OnDblclkTree)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // ״̬��ָʾ��
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};
//ȫ�ֺ���������ַ��������ز�ֵ��ַ�������
int AnalyseStr(CStringArray &strarray, CString str, CString flag)
{
	int nCount;
	int iStart;
	int iEnd;
	CString sTemp;
	nCount = 0;
	iEnd = 0;
	iStart = 0;
	while (iEnd >= 0)
	{
		iEnd = str.Find(flag, iStart);
		if (iEnd >= 0)
		{
			sTemp = str.Mid(iStart, (iEnd - iStart));
			strarray.Add(sTemp);
			iStart = iEnd + 1;
		}
		else if (iEnd < 0)
		{
			sTemp = str.Mid(iStart, (str.GetLength() - iStart));
			strarray.Add(sTemp);
		}

	}
	nCount = strarray.GetSize();
	return nCount;
}

// CMainFrame ����/����

CMainFrame::CMainFrame()
{
	// TODO:  �ڴ���ӳ�Ա��ʼ������
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
	//�������ÿ������ķ��	����ʽ �Լ���
	m_LeftCtrBar.SetBarStyle(m_LeftCtrBar.GetBarStyle() | CBRS_TOOLTIPS
		| CBRS_FLYBY | CBRS_SIZE_DYNAMIC);
	//�������ÿ�����ͣ����λ��  any  ��������λ��
	m_LeftCtrBar.EnableDocking(CBRS_ALIGN_ANY);
	//���������������ͣ�� 
	DockControlBar(&m_LeftCtrBar, AFX_IDW_DOCKBAR_LEFT);      //ͣ�������

	//���ؼ�
	if (!m_wndTree.Create(WS_CHILD | WS_VISIBLE |
		TVS_HASLINES | TVS_HASBUTTONS | TVS_LINESATROOT,
		CRect(0, 0, 0, 0), &m_LeftCtrBar, 100))
	{
		TRACE0("Failed to create instant bar child\n");
		return -1;
	}
	m_wndTree.ModifyStyleEx(0, WS_EX_CLIENTEDGE);

	InitTreeCtrlData();
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

//���һ�� ��װƬ  ϲ��ƬҪ���������ؼ�����ʾ�������е�ӰƬ ��ôŪ  ��� ����˫�� ����ѡ������仯�¼���
//�����Ǹ��¼������ܹ�������һ���������� Ȼ�󿽱���������Ϊ�Ƕ�̬������û�а취�����Ϣӳ�� 
//�����Ǵ����ѡ������仯ʱOnSelchangedTree �����ĺ�������  ��������ô����

void CMainFrame::OnSelchangedTree(NMHDR* pNMHDR, LRESULT* pResult)
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	//2ѡ��ĳһ���ͣ���������ID�����ظ�����������ӰƬ���ƺ�ID
	CString strVideos;
	// find the currently selected item
	HTREEITEM hCurSel = m_wndTree.GetNextItem(TVI_ROOT, TVGN_CARET);
	if (hCurSel == NULL)			//���˺ܶ��ж�  ѡ�и��ڵ�
	{
		AfxMessageBox(_T("��ѡ����ؽڵ㣡"));
		return;
	}
	if (m_wndTree.GetParentItem(hCurSel) == NULL)//�ų����ڵ�  ����������û��ӰƬ���ų����ڵ㣩
	{
		return;
	}
	if (m_wndTree.GetParentItem(m_wndTree.GetParentItem(hCurSel)) != NULL)//�ų���3��Ŀ¼(�����ӰƬ�Ļ�Ҳ����ȥ��ȡ����Ľڵ㡣û��)
	{
		return;
	}
	if (m_wndTree.ItemHasChildren(hCurSel))//��ֹ�ظ����(�������Ѿ���������ֽڵ�Ͳ�Ҫ����ˡ�����ÿ�ζ�ȥ������ռ�ô���  )
	{						//ͨ��ӰƬ��������ӰƬ����ͨ����������Ϣ��ʱ�򲻻�ʵʱ���µ� 
		return;
	}
	DWORD nTypeID = m_wndTree.GetItemData(hCurSel);
	m_clientSock.GetVideosByTypeID(nTypeID, strVideos);//��������ǻ�ȡĳһ���������е�ӰƬ���� ����ID
	CStringArray strArray;
	//�յ����ַ��������ַ���,ȥ����󱻲�ֵĿ��ַ���
	int typeCount = AnalyseStr(strArray, strVideos, ",") - 1;
	HTREEITEM hItem = NULL;
	for (int i = 0; i<typeCount; i++)       //��ȡ��֮�������ǲ���
	{
		if (i % 2 == 0)
		{
			CString strVideoName = strArray.GetAt(i);
			hItem = m_wndTree.InsertItem(strVideoName, hCurSel);//����ڵ� ������Ϊ�ڵ����� 
		}
		else
		{
			DWORD videoID = atoi(strArray.GetAt(i));//ID��Ϊ�ڵ�ĸ������� 
			m_wndTree.SetItemData(hItem, videoID);//�����ID��Ϊ��������  ��Ϊ�ڵ�ĸ�������
		}
	}
	m_wndTree.Expand(hCurSel, TVE_EXPAND);
	*pResult = 0;
}
//˫��ӰƬ   �оͲ��������ˡ�û�о�����  ǰ��Ҳ���ų��ڵ�ġ���Ϊ����ֻҪ��3��ڵ�

void CMainFrame::OnDblclkTree(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: Add your control notification handler code here

	//3 ˫��ĳһ����Ӱ������ID,��̨���ظõ�Ӱ������
	HTREEITEM hSelItem = m_wndTree.GetSelectedItem();
	if (hSelItem == NULL)
	{
		return;
	}
	if (m_wndTree.GetParentItem(hSelItem) == NULL)//�ų����ڵ�
	{
		return;
	}
	if (m_wndTree.GetParentItem(m_wndTree.GetParentItem(hSelItem)) == NULL)//�ų���2��Ŀ¼
	{
		return;
	}

	//������ڵ��ǵ�Ӱ�����б�
	DWORD videoID = m_wndTree.GetItemData(hSelItem);
	CString strID;
	strID.Format("%d", videoID);
	//MessageBox(strID);
	m_clientSock.GetMediaData(videoID, "c:\\", m_strFullPath);// ��ȡ��Ƶ���ݱ��浽C�̸�Ŀ¼ ������ҵ���Ҳ�и�Ĭ��·�����㿴���Ҳ������������ �������Ƿֶ����ص�
	MessageBox(m_strFullPath);//���������Ի��������ȷ���Ϳ�ʼִ��������� 
	CVODClientView* pView = (CVODClientView*)GetActiveView();
	pView->m_wndPlayer.SetUrl(m_strFullPath);    //����

	/*
	CString strFullPath="C:\\����2.wmv";
	CVODClientView* pView=(CVODClientView*)GetActiveView();
	if (pView->m_wndPlayer.GetSafeHwnd())
	{
	pView->m_wndPlayer.SetUrl(strFullPath);
	}
	*/
	*pResult = 0;
}

void CMainFrame::InitTreeCtrlData()//��ܵ�onCreate ʱ�����
{

	HTREEITEM hRoot = m_wndTree.InsertItem("��������");
	CString strAllTypes;
	m_clientSock.GetAllVideoTypes(strAllTypes);//��ȡ���е���Ƶ���� socket��������
	// MessageBox(strAllTypes);
	CStringArray strArray;
	//�յ����ַ��������ַ���,ȥ����󱻲�ֵĿ��ַ���
	int typeCount = AnalyseStr(strArray, strAllTypes, ",") - 1;
	HTREEITEM hItem = NULL;
	for (int i = 0; i<typeCount; i++)
	{
		if (i % 2 == 0)//��2�������� ����Ĳ�����һ��
		{//0 2  4  6  8 10 12  ִ������
			CString strTypeName = strArray.GetAt(i);
			hItem = m_wndTree.InsertItem(strTypeName, hRoot);//��ȡ��֮����뵽���ؼ���
		}
		else//1 3 5 7 9 ִ������
		{
			DWORD typeID = atoi(strArray.GetAt(i));
			m_wndTree.SetItemData(hItem, typeID);
		}
	}

	m_wndTree.SetItemHeight(25);
	m_wndTree.Expand(hRoot, TVE_EXPAND);
}
