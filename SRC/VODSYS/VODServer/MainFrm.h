
// MainFrm.h : CMainFrame ��Ľӿ�
//

#pragma once
#include "DlgVideo.h"// �������Ǹ��Ի��� ���ڹ������� 

#include ".\ado\Ado.h"//���ݿ��װ���ͷ�ļ�

#include "NetServer.h"
class CMainFrame : public CFrameWnd
{
	
protected: // �������л�����
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// ����
public:
	CAdoConnection m_adoConnection;


// ����
public:

// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// ʵ��
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // �ؼ���Ƕ���Ա
	CToolBar          m_wndToolBar;
	CStatusBar        m_wndStatusBar;
	CCoolBar m_LeftCtrBar; //����Ŀ��ƴ���
	CCoolBar m_BottomCtrBar; //������Ŀ��ƴ���
	CTreeCtrl  m_wndTree;  //CMarinFrame��������ӳ�Ա���� 
//	CDlgVideo   m_dlgVideo;//�û��޸���Ƶ��Ϣ�ĶԻ���
public:
	CDlgVideo   m_dlgVideo;//�û��޸���Ƶ��Ϣ�ĶԻ���
	CNetServer m_NetServer;

	// ���ɵ���Ϣӳ�亯��
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
extern CMainFrame * g_pWnd;//������̻߳�ȡ����ܴ���ָ�� �������

