// DlgLogin.cpp : 实现文件
//

#include "stdafx.h"
#include "VODClient.h"
#include "DlgLogin.h"
#include "afxdialogex.h"


// CDlgLogin 对话框

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


// CDlgLogin 消息处理程序


void CDlgLogin::OnOK()
{
	// TODO:  在此添加专用代码和/或调用基类
	// TODO: Add extra validation here
	//登录验证
	UpdateData(TRUE);
	if (!m_clientSock.Login(m_strUserName, m_strPwd))//业务逻辑封装在类里面 这样层次结构会更好
	{
		MessageBox("用户名称或密码错误，请重新登录！");
		return;
	}
	//明天讲今天只是做界面 跟通讯有关的先不管

	CDialog::OnOK();
}
