#if !defined(AFX_DLGOTPTEST_H__B43B123B_EADD_482C_BBBF_620FF1A840EB__INCLUDED_)
#define AFX_DLGOTPTEST_H__B43B123B_EADD_482C_BBBF_620FF1A840EB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DLGOtpTest.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDLGOtpTest dialog

class CDLGOtpTest : public CDialog
{
// Construction
public:
	CDLGOtpTest(CWnd* pParent = NULL);   // standard constructor
	void RefreshSettings();

// Dialog Data
	//{{AFX_DATA(CDLGOtpTest)
	enum { IDD = IDD_TRYPCREADER_DIALOG };
	int		m_nSound;
	CString	m_strAmt1;
	CString	m_strAmt2;
	BOOL	m_bGreen;
	BOOL	m_bRed;
	CString	m_arPath1;
	CString	m_arPath2;
	UINT	m_nBaudRate;
	CString	m_szBListPath;
	CString	m_szCCHSPath;
	int		m_nDayKeep;
	CString	m_szEODPath;
	CString	m_szFWarePath;
	int		m_nHouseKeepType;
	int		m_nPortNum;
	int		m_nTimeOut;
	CString	m_szXPath;
	BOOL	m_bNegVal;
	int		m_nAps;
	long	m_nAvDetail;
	long	m_nAvMach;
	CString	m_szCAN;
	int		m_nClass;
	int		m_nLang;
	CString	m_szRmtV;
	CString	m_szTranTime;
	long	m_nMID;
	CString	m_szddamt;
	double	m_fddAmt;
	double	m_fddRmt;
	double	m_favAmt;
	double	m_favRmt;
	DWORD	m_dwErrCode;
	DWORD	m_dwVerBList;
	DWORD	m_dwCompID;
	DWORD	m_dwVerCCHS;
	DWORD	m_dwVerDev;
	DWORD	m_dwDevTime;
	DWORD	m_dwVerEOD;
	DWORD	m_dwVerFWare;
	DWORD	m_dwVerKey;
	DWORD	m_dwLocID;
	DWORD	m_dwNewLocID;
	DWORD	m_dwOptrID;
	CString	m_szNewXFile;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDLGOtpTest)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDLGOtpTest)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnButton1();
	afx_msg void OnClose();
	afx_msg void OnButton2();
	afx_msg void OnButton6();
	afx_msg void OnButton7();
	afx_msg void OnButton8();
	afx_msg void OnButton9();
	afx_msg void OnButton10();
	afx_msg void OnButton3();
	afx_msg void OnButton4();
	afx_msg void OnButton5();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGOTPTEST_H__B43B123B_EADD_482C_BBBF_620FF1A840EB__INCLUDED_)
