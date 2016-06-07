
// MainFrm.cpp : CMainFrame 类的实现
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
	ID_SEPARATOR,           // 状态行指示器
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame 构造/析构

CMainFrame::CMainFrame()
{
	// TODO:  在此添加成员初始化代码
	//链接数据库 
	BOOL bRet = m_adoConnection.ConnectAccess("../../../DB/VODDB.mdb");
	if (!bRet)
	{
		MessageBox(_T("链接数据库失败！"));
	
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
		TRACE0("未能创建工具栏\n");
		return -1;      // 未能创建
	}

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("未能创建状态栏\n");
		return -1;      // 未能创建
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	// TODO:  如果不需要可停靠工具栏，则删除这三行
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);




	//控制条的创建和停靠
	if (!m_LeftCtrBar.Create(_T("导航控制条"), this, CSize(230, 260), TRUE, 123))
	{
		TRACE0("Failed to create mybar\n");
		return -1;
	}
	if (!m_BottomCtrBar.Create(_T("编辑控制条"), this, CSize(200, 170), TRUE, 124))
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

	DockControlBar(&m_BottomCtrBar, AFX_IDW_DOCKBAR_BOTTOM);  //停靠在底部 
	DockControlBar(&m_LeftCtrBar, AFX_IDW_DOCKBAR_LEFT);      //停靠在左边


	//设置工具栏按钮的文本（系统工具栏） 
	m_wndToolBar.SetButtonText(0, _T(" 类型导航 "));
	m_wndToolBar.SetButtonText(1, _T(" 视频编辑 "));
	//调整工具栏按钮的大小（否则文本显示不出来，它会随着文本的调整而调整）
	/////////////调整工具条/////////////////
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
	//树控件的创建
	if (!m_wndTree.Create((WS_CHILD | WS_VISIBLE | TVS_HASLINES | TVS_HASBUTTONS | TVS_LINESATROOT), CRect(0, 0, 0, 0), &m_LeftCtrBar, 100))
	{
		TRACE0(_T("Failed to create instant bar child\n"));
		return -1;
	}
	//设置树控件的风格 
	m_wndTree.ModifyStyleEx(0, WS_EX_CLIENTEDGE);
	//设置树控件背景色 但是一闪就没了 
	//m_wndTree.SetBkColor(RGB(255, 0, 0)); //PeachPuff
	//对话框 (底部对话框创建显示 和从数据库中加载组合框的内容视频类型 )
	if (!m_dlgVideo.Create(IDD_DLG_VIDEO, &m_BottomCtrBar))
	{
		return -1;
	}
	m_dlgVideo.ShowWindow(SW_SHOW);
	m_dlgVideo.InitVideoTypeCtrl();

	//这个是树控件加载视频内容 上面也已经创建树控件了 
	InitTypeTreeCtrl();
	//启动服务器
	m_NetServer.InitServer();
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO:  在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return TRUE;
}

// CMainFrame 诊断

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


// CMainFrame 消息处理程序



void CMainFrame::OnToolbarNavigate()
{
	// TODO:  在此添加命令处理程序代码

	// TODO: Add your command handler code here
	ShowControlBar(&m_LeftCtrBar, !m_LeftCtrBar.IsVisible(), FALSE);


}


void CMainFrame::OnUpdateToolbarNavigate(CCmdUI *pCmdUI)
{
	// TODO:  在此添加命令更新用户界面处理程序代码

	// TODO: Add your command update UI handler code here

	pCmdUI->SetCheck(m_LeftCtrBar.IsVisible());
}


void CMainFrame::OnToolbarEdit()
{
	// TODO:  在此添加命令处理程序代码
	// TODO: Add your command handler code here
	ShowControlBar(&m_BottomCtrBar, !m_BottomCtrBar.IsVisible(), FALSE);
}
void CMainFrame::OnUpdateToolbarEdit(CCmdUI *pCmdUI)
{
	// TODO:  在此添加命令更新用户界面处理程序代码
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_BottomCtrBar.IsVisible());
}

#include "TypeManager.h"
void CMainFrame::InitTypeTreeCtrl()
{
	//定义访问视频类型类的对象
	CTypeManager typeMgr(&m_adoConnection);
	CList<CType, CType> lstTypes;
	//获取视频类型的信息保存到链表  lstTypes中
	typeMgr.GetAllType(&lstTypes);
	CType type;
	//插入树控件的根节点
	HTREEITEM hRoot = m_wndTree.InsertItem(_T("所有类型"));
	for (int i = 0; i<lstTypes.GetCount(); i++)
	{
		//从链表中获取视频类型的数据
		type = lstTypes.GetAt(lstTypes.FindIndex(i));
		//将视频名称做为树节点名称插入到树控件
		HTREEITEM hItem = m_wndTree.InsertItem(type.strTypeName, hRoot);
		//将视频类型ID作设置为节点的附加数据
		m_wndTree.SetItemData(hItem, type.nTypeID);
	}
	//设置树节点高度
	m_wndTree.SetItemHeight(20);
	//在根节点展开树控件
	m_wndTree.Expand(hRoot, TVE_EXPAND);
}
