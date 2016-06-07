
// MainFrm.h : CMainFrame 类的接口
//

#pragma once
#include "DlgVideo.h"// 最下面是个对话框 放在工具条中 

#include ".\ado\Ado.h"//数据库封装类的头文件

#include "NetServer.h"
class CMainFrame : public CFrameWnd
{
	
protected: // 仅从序列化创建
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// 特性
public:
	CAdoConnection m_adoConnection;


// 操作
public:

// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 实现
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // 控件条嵌入成员
	CToolBar          m_wndToolBar;
	CStatusBar        m_wndStatusBar;
	CCoolBar m_LeftCtrBar; //左面的控制窗口
	CCoolBar m_BottomCtrBar; //最下面的控制窗口
	CTreeCtrl  m_wndTree;  //CMarinFrame类里面添加成员变量 
//	CDlgVideo   m_dlgVideo;//用户修改视频信息的对话框
public:
	CDlgVideo   m_dlgVideo;//用户修改视频信息的对话框
	CNetServer m_NetServer;

	// 生成的消息映射函数
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnToolbarNavigate();
	afx_msg void OnUpdateToolbarNavigate(CCmdUI *pCmdUI);
	afx_msg void OnToolbarEdit();
	afx_msg void OnUpdateToolbarEdit(CCmdUI *pCmdUI);
	void InitTypeTreeCtrl();
};
extern CMainFrame * g_pWnd;//解决子线程获取主框架串口指针 句柄问题

