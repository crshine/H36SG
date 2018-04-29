#if !defined(AFX_DLGSETTINGOTPREADER_H__49421077_1898_488C_96BE_5A2410EFE463__INCLUDED_)
#define AFX_DLGSETTINGOTPREADER_H__49421077_1898_488C_96BE_5A2410EFE463__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// dlgsettingotpreader.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgSettingOtpReader dialog

class CDlgSettingOtpReader : public CDialog
{
// Construction
public:
	CDlgSettingOtpReader(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgSettingOtpReader)
	enum { IDD = IDD_SETTING_OTPREADER };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgSettingOtpReader)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgSettingOtpReader)
	virtual BOOL OnInitDialog();
	afx_msg void OnSetFolders();
	afx_msg void OnReadFolders();
	afx_msg void OnSetTimeReadVer();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSETTINGOTPREADER_H__49421077_1898_488C_96BE_5A2410EFE463__INCLUDED_)
