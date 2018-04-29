#if !defined(AFX_DLGOTP4RECORD_H__677F5260_AC6F_479F_B673_8756D9CD736F__INCLUDED_)
#define AFX_DLGOTP4RECORD_H__677F5260_AC6F_479F_B673_8756D9CD736F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgOTP4Record.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgOTP4Record dialog

class CDlgOTP4Record : public CDialog
{
// Construction
public:
	CDlgOTP4Record(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgOTP4Record)
	enum { IDD = IDD_DLG_OTP_RECORD };
	CListCtrl	m_OTP_Record;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgOTP4Record)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	BOOL CardStatus;
	INT ErrTmp,Err19,Err24;

	// Generated message map functions
	//{{AFX_MSG(CDlgOTP4Record)
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGOTP4RECORD_H__677F5260_AC6F_479F_B673_8756D9CD736F__INCLUDED_)
