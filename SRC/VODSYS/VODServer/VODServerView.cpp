
// VODServerView.cpp : CVODServerView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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

// CVODServerView ����/����

CVODServerView::CVODServerView()
	: CFormView(CVODServerView::IDD)
{
	// TODO:  �ڴ˴���ӹ������

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
	// TODO:  �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CFormView::PreCreateWindow(cs);
}

void CVODServerView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();
	//���ݰ�
	//�õ�����ܴ��е����ݿ����Ӷ���
	CMainFrame *pWnd = (CMainFrame *)AfxGetMainWnd();
	//�����Ӷ������õ���¼��������
	m_adoRecordSet.SetAdoConnection(&pWnd->m_adoConnection);
	//���õ�ǰ�α�λ��Ϊ��ʼλ��
	m_adoRecordSet.SetCursorLocation();
	//����Sql��� ����as ��������ԭ��Ӣ�Ļ������������������ݿ�Ĵ���ͨ���ǲ��ܳ����ڽ��浱�еġ����������ǰ󶨵����Կ��������ǲ���̫�� ���������ǿ����ֲ�Ū��ɾ�Ĳ�Ĳ��� ��
	CString strSql =
		"select videoInfo.id as ���,videoName as ��Ƶ����,videoDesp as ��Ƶ����,videoPath as ��Ƶ·��,typeName as �������� from videoInfo,TypeInfo where videoInfo.typeid = TypeInfo.id";
	//ִ��SQL���
	m_adoRecordSet.Open(strSql,adCmdText);
	//�ŵ���¼��������
	//����ȡ�ļ�¼�������ݰ󶨵�DataGrid�ؼ���
	BindDataGrid(&m_adoRecordSet);
}


// CVODServerView ���

#ifdef _DEBUG
void CVODServerView::AssertValid() const
{
	CFormView::AssertValid();
}

void CVODServerView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CVODServerDoc* CVODServerView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CVODServerDoc)));
	return (CVODServerDoc*)m_pDocument;
}
#endif //_DEBUG


// CVODServerView ��Ϣ�������


void CVODServerView::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	CRect rcClient;
	GetClientRect(&rcClient);
	/*CWnd* pWnd = GetDlgItem(IDC_DATAGRID);
	if (pWnd)
		pWnd->MoveWindow(0, 0, rcClient.Width(), rcClient.Height());
*/
	//���֪�����ڴ��ڲ������أ���������  ( �ѿ������ص��ұߵ���Ƶ��Ϣ�б�Ҳ����󻯵�)
	//m_wndGrid.GetSafeHwnd();//��ȡ�͸ö���m_wndGrid��صĴ��ھ�� 
	if (m_wndGrid.GetSafeHwnd())//�жϿؼ��Ĵ��ھ��
	{
		m_wndGrid.MoveWindow(0, 0, rcClient.Width(), rcClient.Height());
	//ȥ����������(��С������)
		
		//m_wndGrid.put_ScrollBars(0);
		m_wndGrid.SetScrollBars(0);

	}


	//if (m_wndGrid.GetSafeHwnd())
	//{
	//	m_wndGrid.SetScrollBars(0);
	//}

	// TODO:  �ڴ˴������Ϣ����������
}


void CVODServerView::BindDataGrid(CAdoRecordSet * pSet)
{
	//���ÿؼ�������ԴΪ��¼��
	m_wndGrid.SetRefDataSource((LPUNKNOWN)m_adoRecordSet.GetRecordset());
	//m_wndGrid.putref_DataSource((LPUNKNOWN)m_adoRecordSet.GetRecordset());
	
	//������ʾ
	m_wndGrid.Refresh();
}
BEGIN_EVENTSINK_MAP(CVODServerView, CFormView)
	ON_EVENT(CVODServerView, IDC_DATAGRID, 221, CVODServerView::OnSelchangeDatagrid, VTS_PI2)
END_EVENTSINK_MAP()

#include "column.h"
#include "columns.h"

void CVODServerView::OnSelchangeDatagrid(short* Cancel)
{
	// TODO:  �ڴ˴������Ϣ����������
	// TODO: Add your control notification handler code here
	//��ȡ����ܴ���
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	//��ǰ��������е���������λ����ǰ�У�
	_variant_t varRow((long)(m_wndGrid.GetRow() + 1));
	//GetItem�Ĳ���ʱ�е�����ֵ
	CString strID = m_wndGrid.GetColumns().GetItem(_variant_t((long)0)).CellText(varRow);

	CString strName = m_wndGrid.GetColumns().GetItem(_variant_t((long)1)).CellText(varRow);
	CString strDesp = m_wndGrid.GetColumns().GetItem(_variant_t((long)2)).CellText(varRow);
	CString strPath = m_wndGrid.GetColumns().GetItem(_variant_t((long)3)).CellText(varRow);
	CString strType = m_wndGrid.GetColumns().GetItem(_variant_t((long)4)).CellText(varRow);
	//��datagrid�ؼ��е�ֵ��ֵ���Ի������ؿؼ�
	pMainFrame->m_dlgVideo.m_strVideoID = strID;
	pMainFrame->m_dlgVideo.m_strVideoName = strName;
	pMainFrame->m_dlgVideo.m_strVideoType = strType;
	pMainFrame->m_dlgVideo.m_strVideoPath = strPath;
	pMainFrame->m_dlgVideo.m_strVideoDesp = strDesp;
	//pMainFrame->m_dlgVideo.UpdateData(FALSE);
	//���ð�ť���ı��ɲ����Ϊ����
	pMainFrame->m_dlgVideo.m_wndOK.SetWindowText("����");
}
