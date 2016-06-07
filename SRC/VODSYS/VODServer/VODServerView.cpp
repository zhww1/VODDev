
// VODServerView.cpp : CVODServerView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "VODServer.h"
#endif

#include "VODServerDoc.h"
#include "VODServerView.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CVODServerView

IMPLEMENT_DYNCREATE(CVODServerView, CFormView)

BEGIN_MESSAGE_MAP(CVODServerView, CFormView)
	ON_WM_SIZE()
END_MESSAGE_MAP()

// CVODServerView 构造/析构

CVODServerView::CVODServerView()
	: CFormView(CVODServerView::IDD)
{
	// TODO:  在此处添加构造代码

}

CVODServerView::~CVODServerView()
{
}

void CVODServerView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DATAGRID, m_wndGrid);
}

BOOL CVODServerView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CFormView::PreCreateWindow(cs);
}

void CVODServerView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();
	//数据绑定
	//得到主框架窗中的数据库链接对象
	CMainFrame *pWnd = (CMainFrame *)AfxGetMainWnd();
	//将链接对象设置到记录集对象上
	m_adoRecordSet.SetAdoConnection(&pWnd->m_adoConnection);
	//设置当前游标位置为开始位置
	m_adoRecordSet.SetCursorLocation();
	//定义Sql语句 做了as 重命名把原来英文换成中文名（访问数据库的代码通常是不能出现在界面当中的。由于这里是绑定的所以可以允许但是不能太多 ，下面我们看看分层弄增删改查的操作 ）
	CString strSql =
		"select videoInfo.id as 编号,videoName as 视频名称,videoDesp as 视频描述,videoPath as 视频路径,typeName as 所属类型 from videoInfo,TypeInfo where videoInfo.typeid = TypeInfo.id";
	//执行SQL语句
	m_adoRecordSet.Open(strSql,adCmdText);
	//放到记录集当中了
	//将获取的记录集的数据绑定到DataGrid控件上
	BindDataGrid(&m_adoRecordSet);
}


// CVODServerView 诊断

#ifdef _DEBUG
void CVODServerView::AssertValid() const
{
	CFormView::AssertValid();
}

void CVODServerView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CVODServerDoc* CVODServerView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CVODServerDoc)));
	return (CVODServerDoc*)m_pDocument;
}
#endif //_DEBUG


// CVODServerView 消息处理程序


void CVODServerView::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	CRect rcClient;
	GetClientRect(&rcClient);
	/*CWnd* pWnd = GetDlgItem(IDC_DATAGRID);
	if (pWnd)
		pWnd->MoveWindow(0, 0, rcClient.Width(), rcClient.Height());
*/
	//如何知道窗口存在不存在呢？掉个函数  ( 把控制条关掉右边的视频信息列表也是最大化的)
	//m_wndGrid.GetSafeHwnd();//获取和该对象m_wndGrid相关的窗口句柄 
	if (m_wndGrid.GetSafeHwnd())//判断控件的窗口句柄
	{
		m_wndGrid.MoveWindow(0, 0, rcClient.Width(), rcClient.Height());
	//去掉滚动条的(缩小看下面)
		
		//m_wndGrid.put_ScrollBars(0);
		m_wndGrid.SetScrollBars(0);

	}


	//if (m_wndGrid.GetSafeHwnd())
	//{
	//	m_wndGrid.SetScrollBars(0);
	//}

	// TODO:  在此处添加消息处理程序代码
}


void CVODServerView::BindDataGrid(CAdoRecordSet * pSet)
{
	//设置控件的数据源为记录集
	m_wndGrid.SetRefDataSource((LPUNKNOWN)m_adoRecordSet.GetRecordset());
	//m_wndGrid.putref_DataSource((LPUNKNOWN)m_adoRecordSet.GetRecordset());
	
	//更新显示
	m_wndGrid.Refresh();
}
BEGIN_EVENTSINK_MAP(CVODServerView, CFormView)
	ON_EVENT(CVODServerView, IDC_DATAGRID, 221, CVODServerView::OnSelchangeDatagrid, VTS_PI2)
END_EVENTSINK_MAP()

#include "column.h"
#include "columns.h"

void CVODServerView::OnSelchangeDatagrid(short* Cancel)
{
	// TODO:  在此处添加消息处理程序代码
	// TODO: Add your control notification handler code here
	//获取主框架窗口
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	//当前鼠标所在行的索引（定位到当前行）
	_variant_t varRow((long)(m_wndGrid.GetRow() + 1));
	//GetItem的参数时列的索引值
	CString strID = m_wndGrid.GetColumns().GetItem(_variant_t((long)0)).CellText(varRow);

	CString strName = m_wndGrid.GetColumns().GetItem(_variant_t((long)1)).CellText(varRow);
	CString strDesp = m_wndGrid.GetColumns().GetItem(_variant_t((long)2)).CellText(varRow);
	CString strPath = m_wndGrid.GetColumns().GetItem(_variant_t((long)3)).CellText(varRow);
	CString strType = m_wndGrid.GetColumns().GetItem(_variant_t((long)4)).CellText(varRow);
	//将datagrid控件中的值赋值给对话框的相关控件
	pMainFrame->m_dlgVideo.m_strVideoID = strID;
	pMainFrame->m_dlgVideo.m_strVideoName = strName;
	pMainFrame->m_dlgVideo.m_strVideoType = strType;
	pMainFrame->m_dlgVideo.m_strVideoPath = strPath;
	pMainFrame->m_dlgVideo.m_strVideoDesp = strDesp;
	//pMainFrame->m_dlgVideo.UpdateData(FALSE);
	//设置按钮的文本由插入变为更新
	pMainFrame->m_dlgVideo.m_wndOK.SetWindowText("更新");
}
