#if !defined(AFX_DLGSETTINGPERMISSION_H__CC27AECA_8527_437D_B1E7_01BA313630F8__INCLUDED_)
#define AFX_DLGSETTINGPERMISSION_H__CC27AECA_8527_437D_B1E7_01BA313630F8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// dlgsettingpermission.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgSettingPermission dialog

class CDlgSettingPermission : public CDialog
{
// Construction
public:
	CDlgSettingPermission(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgSettingPermission)
	enum { IDD = IDD_SETTING_PERMISSION };
	CListCtrl	m_list;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgSettingPermission)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgSettingPermission)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void Show();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSETTINGPERMISSION_H__CC27AECA_8527_437D_B1E7_01BA313630F8__INCLUDED_)
