#if !defined(AFX_DLGRATETIMEZONE_H__F049175E_7F8A_4EBE_AD95_C04348FFF256__INCLUDED_)
#define AFX_DLGRATETIMEZONE_H__F049175E_7F8A_4EBE_AD95_C04348FFF256__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// dlgratetimezone.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgRateTimezone dialog

class CDlgRateTimezone : public CDialog
{
// Construction
public:
	void ShowTheRule();
	CDlgRateTimezone(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgRateTimezone)
	enum { IDD = IDD_RATE_TIMEZONE };
	CListCtrl	m_list;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgRateTimezone)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgRateTimezone)
	afx_msg void OnButtonRefrash();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CString showHHMM(short mins);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGRATETIMEZONE_H__F049175E_7F8A_4EBE_AD95_C04348FFF256__INCLUDED_)
