#if !defined(AFX_DLGEXITCONFIRM_H__43C52C54_7716_479C_A83A_3E69F72A155C__INCLUDED_)
#define AFX_DLGEXITCONFIRM_H__43C52C54_7716_479C_A83A_3E69F72A155C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgExitConfirm.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgExitConfirm dialog

class CDlgExitConfirm : public CDialog
{
// Construction
public:
	CDlgExitConfirm(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgExitConfirm)
	enum { IDD = IDD_DLG_CONFEXIT };
	CDateTimeCtrl	m_Calendar; // [PY]: 07 Jun 2005 - the Exit date,
	CDateTimeCtrl	m_Time;		// Exit time and
	CEdit	m_ExitStnEdit;		// Exit station edit fields
	int		m_nTicketType;
	int		m_nCardTypeOTP;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgExitConfirm)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CString _CardNo;
	CFont m_fontEdit;
	void InitControl();
	// Generated message map functions
	//{{AFX_MSG(CDlgExitConfirm)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnButton2();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus); // [PY]: 07 Jun 2005 - display default values
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGEXITCONFIRM_H__43C52C54_7716_479C_A83A_3E69F72A155C__INCLUDED_)
