
// VODServerView.h : CVODServerView 类的接口
//

#pragma once

#include "resource.h"
#include "datagrid.h"

#include "VODServerDoc.h"
class CVODServerView : public CFormView
{
protected: // 仅从序列化创建
	CVODServerView();
	DECLARE_DYNCREATE(CVODServerView)

public:
	enum{ IDD = IDD_VODSERVER_FORM };

// 特性
public:
	CVODServerDoc* GetDocument() const;
	CAdoRecordSet m_adoRecordSet;//记录集对象 

// 操作
public:

// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual void OnInitialUpdate(); // 构造后第一次调用

// 实现
public:
	virtual ~CVODServerView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
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

#ifndef _DEBUG  // VODServerView.cpp 中的调试版本
inline CVODServerDoc* CVODServerView::GetDocument() const
   { return reinterpret_cast<CVODServerDoc*>(m_pDocument); }
#endif

