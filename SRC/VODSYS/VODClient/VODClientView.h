
// VODClientView.h : CVODClientView ��Ľӿ�
//

#pragma once

#include "resource.h"
#include "wmpplayer4.h"
#include "VODClientDoc.h"
class CVODClientView : public CFormView
{
protected: // �������л�����
	CVODClientView();
	DECLARE_DYNCREATE(CVODClientView)

public:
	enum{ IDD = IDD_VODCLIENT_FORM };
	CWMPPlayer4  m_wndPlayer;
// ����
public:
	CVODClientDoc* GetDocument() const;

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
	virtual ~CVODClientView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	DECLARE_EVENTSINK_MAP()
	void OnDoubleclickMediaPlayer(short nButton, short nShiftState, long fX, long fY);
};

#ifndef _DEBUG  // VODClientView.cpp �еĵ��԰汾
inline CVODClientDoc* CVODClientView::GetDocument() const
   { return reinterpret_cast<CVODClientDoc*>(m_pDocument); }
#endif

