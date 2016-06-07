
// MainFrm.cpp : CMainFrame 类的实现
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
	ON_NOTIFY(TVN_SELCHANGED, 100, OnSelchangedTree)  //这个100要根据动态创建树控件的ID  是100
	ON_NOTIFY(NM_DBLCLK, 100, OnDblclkTree)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // 状态行指示器
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};
//全局函数，拆分字符串，返回拆分的字符串数量
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

// CMainFrame 构造/析构

CMainFrame::CMainFrame()
{
	// TODO:  在此添加成员初始化代码
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
	//这是设置控制条的风格	或样式 自己看
	m_LeftCtrBar.SetBarStyle(m_LeftCtrBar.GetBarStyle() | CBRS_TOOLTIPS
		| CBRS_FLYBY | CBRS_SIZE_DYNAMIC);
	//这是设置控制条停靠的位置  any  就是任意位置
	m_LeftCtrBar.EnableDocking(CBRS_ALIGN_ANY);
	//下面这才是真正的停靠 
	DockControlBar(&m_LeftCtrBar, AFX_IDW_DOCKBAR_LEFT);      //停靠在左边

	//树控件
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

//点击一下 古装片  喜剧片要马上在树控件下显示出它所有的影片 怎么弄  点击 不是双击 还是选择项发生变化事件。
//不管那个事件，都能够从另外一个工程生成 然后拷贝过来。因为是动态创建的没有办法添加消息映射 
//这里是处理的选择项发生变化时OnSelchangedTree 这样的函数里面  看它是怎么处理

void CMainFrame::OnSelchangedTree(NMHDR* pNMHDR, LRESULT* pResult)
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	//2选中某一类型，发送类型ID，返回该类型下所有影片名称和ID
	CString strVideos;
	// find the currently selected item
	HTREEITEM hCurSel = m_wndTree.GetNextItem(TVI_ROOT, TVGN_CARET);
	if (hCurSel == NULL)			//做了很多判断  选中个节点
	{
		AfxMessageBox(_T("请选中相关节点！"));
		return;
	}
	if (m_wndTree.GetParentItem(hCurSel) == NULL)//排除根节点  （所有类型没有影片，排除根节点）
	{
		return;
	}
	if (m_wndTree.GetParentItem(m_wndTree.GetParentItem(hCurSel)) != NULL)//排除第3层目录(如果是影片的话也不用去获取下面的节点。没有)
	{
		return;
	}
	if (m_wndTree.ItemHasChildren(hCurSel))//防止重复添加(就是我已经有了这个字节点就不要添加了。不用每次都去交互了占用带宽  )
	{						//通常影片服务器的影片更新通常在人们休息的时候不会实时更新的 
		return;
	}
	DWORD nTypeID = m_wndTree.GetItemData(hCurSel);
	m_clientSock.GetVideosByTypeID(nTypeID, strVideos);//这个函数是获取某一类型下所有的影片名称 、和ID
	CStringArray strArray;
	//收到的字符串最后的字符是,去掉最后被拆分的空字符串
	int typeCount = AnalyseStr(strArray, strVideos, ",") - 1;
	HTREEITEM hItem = NULL;
	for (int i = 0; i<typeCount; i++)       //获取到之后下面是插入
	{
		if (i % 2 == 0)
		{
			CString strVideoName = strArray.GetAt(i);
			hItem = m_wndTree.InsertItem(strVideoName, hCurSel);//插入节点 名称作为节点名称 
		}
		else
		{
			DWORD videoID = atoi(strArray.GetAt(i));//ID作为节点的附加数据 
			m_wndTree.SetItemData(hItem, videoID);//如果是ID作为附加数据  作为节点的附加数据
		}
	}
	m_wndTree.Expand(hCurSel, TVE_EXPAND);
	*pResult = 0;
}
//双击影片   有就不用下载了。没有就下载  前面也是排除节点的。因为我们只要第3层节点

void CMainFrame::OnDblclkTree(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: Add your control notification handler code here

	//3 双击某一部电影，发送ID,后台下载该电影并播放
	HTREEITEM hSelItem = m_wndTree.GetSelectedItem();
	if (hSelItem == NULL)
	{
		return;
	}
	if (m_wndTree.GetParentItem(hSelItem) == NULL)//排除根节点
	{
		return;
	}
	if (m_wndTree.GetParentItem(m_wndTree.GetParentItem(hSelItem)) == NULL)//排除第2层目录
	{
		return;
	}

	//第三层节点是电影名称列表
	DWORD videoID = m_wndTree.GetItemData(hSelItem);
	CString strID;
	strID.Format("%d", videoID);
	//MessageBox(strID);
	m_clientSock.GetMediaData(videoID, "c:\\", m_strFullPath);// 获取视频数据保存到C盘根目录 包括商业软件也有个默认路径当你看完后也就下载下来了 它可能是分段下载的
	MessageBox(m_strFullPath);//弹出阻塞对话框你点了确定就开始执行下面代码 
	CVODClientView* pView = (CVODClientView*)GetActiveView();
	pView->m_wndPlayer.SetUrl(m_strFullPath);    //播放

	/*
	CString strFullPath="C:\\相亲2.wmv";
	CVODClientView* pView=(CVODClientView*)GetActiveView();
	if (pView->m_wndPlayer.GetSafeHwnd())
	{
	pView->m_wndPlayer.SetUrl(strFullPath);
	}
	*/
	*pResult = 0;
}

void CMainFrame::InitTreeCtrlData()//框架的onCreate 时候调用
{

	HTREEITEM hRoot = m_wndTree.InsertItem("所有类型");
	CString strAllTypes;
	m_clientSock.GetAllVideoTypes(strAllTypes);//获取所有的视频类型 socket类里面做
	// MessageBox(strAllTypes);
	CStringArray strArray;
	//收到的字符串最后的字符是,去掉最后被拆分的空字符串
	int typeCount = AnalyseStr(strArray, strAllTypes, ",") - 1;
	HTREEITEM hItem = NULL;
	for (int i = 0; i<typeCount; i++)
	{
		if (i % 2 == 0)//对2求余区分 下面的操作不一样
		{//0 2  4  6  8 10 12  执行这里
			CString strTypeName = strArray.GetAt(i);
			hItem = m_wndTree.InsertItem(strTypeName, hRoot);//获取到之后插入到树控件上
		}
		else//1 3 5 7 9 执行这里
		{
			DWORD typeID = atoi(strArray.GetAt(i));
			m_wndTree.SetItemData(hItem, typeID);
		}
	}

	m_wndTree.SetItemHeight(25);
	m_wndTree.Expand(hRoot, TVE_EXPAND);
}
