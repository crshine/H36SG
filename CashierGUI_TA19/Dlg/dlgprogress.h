#if !defined(AFX_DLGPROGRESS_H__504ED8A8_CFCE_47AD_B644_9C95A7D919C7__INCLUDED_)
#define AFX_DLGPROGRESS_H__504ED8A8_CFCE_47AD_B644_9C95A7D919C7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgProgress.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgProgress dialog

class CDlgProgress : public CDialog
{
// Construction
public:
	CDlgProgress(UINT Second, CString OperateName, CWnd* pParent = NULL);

// Dialog Data
	//{{AFX_DATA(CDlgProgress)
	enum { IDD = IDD_PROGRESS };
	CProgressCtrl	m_Progress;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgProgress)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CDlgProgress(CWnd* pParent = NULL);   // standard constructor

	// Generated message map functions
	//{{AFX_MSG(CDlgProgress)
	afx_msg void OnTimer(UINT nIDEvent);
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void InitControl();
	const UINT		_EventID/* =1*/;
	const UINT		_TimerStep/* =100*/;		//进度显示步长0.1秒
	CString			_Operate;	//操作名称.
	UINT			_TotalStep;	//操作长度以步长为单位.
	UINT			_EventTimerID;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPROGRESS_H__504ED8A8_CFCE_47AD_B644_9C95A7D919C7__INCLUDED_)
