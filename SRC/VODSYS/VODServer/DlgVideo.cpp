// DlgVideo.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "VODServer.h"
#include "DlgVideo.h"
#include "afxdialogex.h"





// CDlgVideo �Ի���

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


// CDlgVideo ��Ϣ�������
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
		//���������ĸ�������
		m_cboType.SetItemData(i, type.nTypeID);
	}
}


void CDlgVideo::OnClickedNew()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	ClearCtrlData();
	//��ť�����ɸ��±�Ϊ����
	m_wndOK.SetWindowText("����");
}

#include "VideoManager.h"

void CDlgVideo::OnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	// TODO: Add your control notification handler code here

	CMainFrame *pWnd = (CMainFrame*)AfxGetMainWnd();//�õ������ھ��
	CVideoManager videoMgr(&pWnd->m_adoConnection);//����������������� ɾ �� ���������ݴ��ھ���������Ӷ����ȡ���Ӷ����ַ ��
	UpdateData(TRUE);//�ѿؼ�״̬���ݸ��󶨵ı��� 
	if (m_strVideoType == "")
	{
		MessageBox("��ѡ����Ƶ���ͣ�");
		return;
	}
	//��ȡ��ǰ���ı�
	CVideo v;
	v.strVideoName = m_strVideoName;
	v.strVideoDesp = m_strVideoDesp;
	v.strVideoPath = m_strVideoPath;
	int nCurSel = m_cboType.GetCurSel();
	v.nTypeid = m_cboType.GetItemData(nCurSel);
	


	if (m_strVideoID == "")//ִ�в������
	{
		//ִ�в������
		videoMgr.InsertVideo(v);
		//���ԭ������
		ClearCtrlData();
	}
	else//ִ�и��²���
	{
		v.nVideoID = atoi(m_strVideoID);
		//ִ�и������ݲ���
		videoMgr.UpdateVideo(v, v.nVideoID);

	}
	//�����ִ�в���ֻ�����ݿ����Ѿ���������

	BindDataGrid();//�˺��������ݿ����select��ѯ���ؼ���ʾ 
	//test
	UpdateData(FALSE);
}
void CDlgVideo::OnClickedDel()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	// TODO: Add your control notification handler code here
	CMainFrame *pWnd = (CMainFrame*)AfxGetMainWnd();
	CVideoManager videoMgr(&pWnd->m_adoConnection);
	int nVideoID = atoi(m_strVideoID);
	videoMgr.DeleteVideo(nVideoID);//����ֻ������ɾ���� ���ݷ��ʲ�ɵ� 
	//���ԭ������
	ClearCtrlData();
	//���°���ʾ
	BindDataGrid();
	m_wndOK.SetWindowText("����");
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
		"select videoInfo.id as ���,videoName as ��Ƶ����,videoDesp as ��Ƶ����,videoPath as ��Ƶ·��,typeName as �������� from videoInfo,TypeInfo where videoInfo.typeid=TypeInfo.id";
	m_Recordset.Open(strSql, adCmdText);
	CVODServerView *pView = (CVODServerView *)((CFrameWnd*)AfxGetMainWnd())->GetActiveView();
	pView->m_wndGrid.SetRefDataSource((LPUNKNOWN)m_Recordset.GetRecordset());
	pView->m_wndGrid.Refresh();
}


void CDlgVideo::OnClickedOpenfile()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	CFileDialog dlg(TRUE);
	if (IDOK != dlg.DoModal())return;
	m_strVideoPath = dlg.GetPathName();
	UpdateData(FALSE);
}
