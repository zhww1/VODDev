// DlgVideo.cpp : 实现文件
//

#include "stdafx.h"
#include "VODServer.h"
#include "DlgVideo.h"
#include "afxdialogex.h"





// CDlgVideo 对话框

IMPLEMENT_DYNAMIC(CDlgVideo, CDialogEx)

CDlgVideo::CDlgVideo(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgVideo::IDD, pParent)
	, m_strVideoID(_T(""))
	, m_strVideoName(_T(""))
	, m_strVideoPath(_T(""))
	, m_strVideoType(_T(""))
	, m_strVideoDesp(_T(""))
{

}

CDlgVideo::~CDlgVideo()
{
}

void CDlgVideo::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_VIDEO_ID, m_strVideoID);
	DDX_Text(pDX, IDC_VIDEO_NAME, m_strVideoName);
	DDX_Text(pDX, IDC_VIDEO_PATH, m_strVideoPath);
	DDX_CBString(pDX, IDC_VIDEO_TYPE, m_strVideoType);
	DDX_Text(pDX, IDC_VIDEO_DESP, m_strVideoDesp);
	DDX_Control(pDX, IDC_OK, m_wndOK);
	DDX_Control(pDX, IDC_VIDEO_TYPE, m_cboType);
}


BEGIN_MESSAGE_MAP(CDlgVideo, CDialogEx)
	ON_BN_CLICKED(IDC_NEW, &CDlgVideo::OnClickedNew)
	ON_BN_CLICKED(IDC_OK, &CDlgVideo::OnClickedOk)
	ON_BN_CLICKED(IDC_DEL, &CDlgVideo::OnClickedDel)
	ON_BN_CLICKED(IDC_OPENFILE, &CDlgVideo::OnClickedOpenfile)
END_MESSAGE_MAP()


// CDlgVideo 消息处理程序
#include "MainFrm.h"
#include "TypeManager.h"

void CDlgVideo::InitVideoTypeCtrl()
{
	CMainFrame *pWnd = (CMainFrame*)AfxGetMainWnd();
	CTypeManager typeMgr(&pWnd->m_adoConnection);
	CList<CType, CType> lstTypes;
	typeMgr.GetAllType(&lstTypes);
	CType type;
	for (int i = 0; i<lstTypes.GetCount(); i++)
	{
		type = lstTypes.GetAt(lstTypes.FindIndex(i));
		m_cboType.AddString(type.strTypeName);
		//添加数据项的附加数据
		m_cboType.SetItemData(i, type.nTypeID);
	}
}


void CDlgVideo::OnClickedNew()
{
	// TODO:  在此添加控件通知处理程序代码
	ClearCtrlData();
	//按钮名称由更新变为插入
	m_wndOK.SetWindowText("插入");
}

#include "VideoManager.h"

void CDlgVideo::OnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	// TODO: Add your control notification handler code here

	CMainFrame *pWnd = (CMainFrame*)AfxGetMainWnd();//得到主窗口句柄
	CVideoManager videoMgr(&pWnd->m_adoConnection);//创建对象里面包含增 删 改 （参数根据窗口句柄掉了链接对象获取链接对象地址 ）
	UpdateData(TRUE);//把控件状态传递给绑定的变量 
	if (m_strVideoType == "")
	{
		MessageBox("请选择视频类型！");
		return;
	}
	//获取当前的文本
	CVideo v;
	v.strVideoName = m_strVideoName;
	v.strVideoDesp = m_strVideoDesp;
	v.strVideoPath = m_strVideoPath;
	int nCurSel = m_cboType.GetCurSel();
	v.nTypeid = m_cboType.GetItemData(nCurSel);
	


	if (m_strVideoID == "")//执行插入操作
	{
		//执行插入操作
		videoMgr.InsertVideo(v);
		//清空原有数据
		ClearCtrlData();
	}
	else//执行更新操作
	{
		v.nVideoID = atoi(m_strVideoID);
		//执行更新数据操作
		videoMgr.UpdateVideo(v, v.nVideoID);

	}
	//上面的执行操作只是数据库中已经插入或更新

	BindDataGrid();//此函数从数据库从新select查询到控件显示 
	//test
	UpdateData(FALSE);
}
void CDlgVideo::OnClickedDel()
{
	// TODO:  在此添加控件通知处理程序代码
	// TODO: Add your control notification handler code here
	CMainFrame *pWnd = (CMainFrame*)AfxGetMainWnd();
	CVideoManager videoMgr(&pWnd->m_adoConnection);
	int nVideoID = atoi(m_strVideoID);
	videoMgr.DeleteVideo(nVideoID);//这里只是数据删除了 数据访问层干的 
	//清空原有数据
	ClearCtrlData();
	//重新绑定显示
	BindDataGrid();
	m_wndOK.SetWindowText("插入");
}


void CDlgVideo::ClearCtrlData()
{
	m_strVideoID = "";
	m_strVideoName = "";
	m_strVideoDesp = "";
	m_strVideoType = "";
	m_strVideoPath = "";
	UpdateData(FALSE);
}

#include "VODServerView.h"
void CDlgVideo::BindDataGrid()
{
	CMainFrame *pWnd = (CMainFrame*)AfxGetMainWnd();
	m_Recordset.SetAdoConnection(&pWnd->m_adoConnection);
	m_Recordset.SetCursorLocation();
	CString strSql =
		"select videoInfo.id as 编号,videoName as 视频名称,videoDesp as 视频描述,videoPath as 视频路径,typeName as 所属类型 from videoInfo,TypeInfo where videoInfo.typeid=TypeInfo.id";
	m_Recordset.Open(strSql, adCmdText);
	CVODServerView *pView = (CVODServerView *)((CFrameWnd*)AfxGetMainWnd())->GetActiveView();
	pView->m_wndGrid.SetRefDataSource((LPUNKNOWN)m_Recordset.GetRecordset());
	pView->m_wndGrid.Refresh();
}


void CDlgVideo::OnClickedOpenfile()
{
	// TODO:  在此添加控件通知处理程序代码
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	CFileDialog dlg(TRUE);
	if (IDOK != dlg.DoModal())return;
	m_strVideoPath = dlg.GetPathName();
	UpdateData(FALSE);
}
