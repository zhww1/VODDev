// DlgLogin.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "VODClient.h"
#include "DlgLogin.h"
#include "afxdialogex.h"


// CDlgLogin �Ի���

IMPLEMENT_DYNAMIC(CDlgLogin, CDialog)

CDlgLogin::CDlgLogin(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgLogin::IDD, pParent)
	, m_strUserName(_T(""))
	, m_strPwd(_T(""))
{

}

CDlgLogin::~CDlgLogin()
{
}

void CDlgLogin::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_USERNAME, m_strUserName);
	DDX_Text(pDX, IDC_PASSWORD, m_strPwd);
}


BEGIN_MESSAGE_MAP(CDlgLogin, CDialog)
END_MESSAGE_MAP()


// CDlgLogin ��Ϣ�������


void CDlgLogin::OnOK()
{
	// TODO:  �ڴ����ר�ô����/����û���
	// TODO: Add extra validation here
	//��¼��֤
	UpdateData(TRUE);
	if (!m_clientSock.Login(m_strUserName, m_strPwd))//ҵ���߼���װ�������� ������νṹ�����
	{
		MessageBox("�û����ƻ�������������µ�¼��");
		return;
	}
	//���콲����ֻ�������� ��ͨѶ�йص��Ȳ���

	CDialog::OnOK();
}
