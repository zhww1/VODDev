
// VODServerView.h : CVODServerView ��Ľӿ�
//

#pragma once

#include "resource.h"
#include "datagrid.h"

#include "VODServerDoc.h"
class CVODServerView : public CFormView
{
protected: // �������л�����
	CVODServerView();
	DECLARE_DYNCREATE(CVODServerView)

public:
	enum{ IDD = IDD_VODSERVER_FORM };

// ����
public:
	CVODServerDoc* GetDocument() const;
	CAdoRecordSet m_adoRecordSet;//��¼������ 

// ����
public:

// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual void OnInitialUpdate(); // ������һ�ε���

// ʵ��
public:
	virtual ~CVODServerView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	//CDatagrid m_wndGrid;
	CDataGrid m_wndGrid;
	afx_msg void OnSize(UINT nType, int cx, int cy);
	void BindDataGrid(CAdoRecordSet * pSet);
	DECLARE_EVENTSINK_MAP()
	void OnSelchangeDatagrid(short* Cancel);
};

#ifndef _DEBUG  // VODServerView.cpp �еĵ��԰汾
inline CVODServerDoc* CVODServerView::GetDocument() const
   { return reinterpret_cast<CVODServerDoc*>(m_pDocument); }
#endif

