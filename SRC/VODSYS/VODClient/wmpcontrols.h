#if !defined(AFX_WMPCONTROLS_H__27B9DA13_0B76_42A4_843F_532816B029DD__INCLUDED_)
#define AFX_WMPCONTROLS_H__27B9DA13_0B76_42A4_843F_532816B029DD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.


// Dispatch interfaces referenced by this interface
class CWMPMedia;

/////////////////////////////////////////////////////////////////////////////
// CWMPControls wrapper class

class CWMPControls : public COleDispatchDriver
{
public:
	CWMPControls() {}		// Calls COleDispatchDriver default constructor
	CWMPControls(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CWMPControls(const CWMPControls& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	BOOL GetIsAvailable(LPCTSTR bstrItem);
	void play();
	void stop();
	void pause();
	void fastForward();
	void fastReverse();
	double GetCurrentPosition();
	void SetCurrentPosition(double newValue);
	CString GetCurrentPositionString();
	void next();
	void previous();
	CWMPMedia GetCurrentItem();
	void SetCurrentItem(LPDISPATCH newValue);
	long GetCurrentMarker();
	void SetCurrentMarker(long nNewValue);
	void playItem(LPDISPATCH pIWMPMedia);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WMPCONTROLS_H__27B9DA13_0B76_42A4_843F_532816B029DD__INCLUDED_)
