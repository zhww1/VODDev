
// VODClientView.h : CVODClientView 类的接口
//

#pragma once

#include "resource.h"
#include "wmpplayer4.h"
#include "VODClientDoc.h"
class CVODClientView : public CFormView
{
protected: // 仅从序列化创建
	CVODClientView();
	DECLARE_DYNCREATE(CVODClientView)

public:
	enum{ IDD = IDD_VODCLIENT_FORM };
	CWMPPlayer4  m_wndPlayer;
// 特性
public:
	CVODClientDoc* GetDocument() const;

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
	virtual ~CVODClientView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	DECLARE_EVENTSINK_MAP()
	void OnDoubleclickMediaPlayer(short nButton, short nShiftState, long fX, long fY);
};

#ifndef _DEBUG  // VODClientView.cpp 中的调试版本
inline CVODClientDoc* CVODClientView::GetDocument() const
   { return reinterpret_cast<CVODClientDoc*>(m_pDocument); }
#endif

