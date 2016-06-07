#pragma once
#include "afxwin.h"


// CDlgVideo 对话框

class CDlgVideo : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgVideo)

public:
	CDlgVideo(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgVideo();
	CAdoRecordSet m_Recordset;
// 对话框数据
	enum { IDD = IDD_DLG_VIDEO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_strVideoID;
	CString m_strVideoName;
	CString m_strVideoPath;
	CString m_strVideoType;
	CString m_strVideoDesp;
	CButton m_wndOK;
	CComboBox m_cboType;
	void InitVideoTypeCtrl();
	afx_msg void OnClickedNew();
	afx_msg void OnClickedOk();
	afx_msg void OnClickedDel();
	void ClearCtrlData();
	void BindDataGrid();
	afx_msg void OnClickedOpenfile();
};
