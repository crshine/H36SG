#if !defined(AFX_DLGSETTINGCOMMUNICATE_H__34B8A209_86C2_4958_80A1_871884588982__INCLUDED_)
#define AFX_DLGSETTINGCOMMUNICATE_H__34B8A209_86C2_4958_80A1_871884588982__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// dlgsettingcommunicate.h : header file
//
#include "DlgInput.h"
/////////////////////////////////////////////////////////////////////////////
// CDlgSettingCommunicate dialog

class CDlgSettingCommunicate : public CDlgInput
{
// Construction
public:
	CDlgSettingCommunicate(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgSettingCommunicate)
	enum { IDD = IDD_SETTING_COMMUNICATE };
	CIPAddressCtrl	m_StationIP;
	CIPAddressCtrl	m_MNT_IP;
	short	m_MNT_ID;
	short	m_RecvPort;
	short	m_SendPort;
	short	m_SendTreadStep;
	short	m_StationID;
	CString	m_StationName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgSettingCommunicate)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgSettingCommunicate)
	afx_msg void OnUpdateStationId();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void GetLocalIP();
	void InitControl();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSETTINGCOMMUNICATE_H__34B8A209_86C2_4958_80A1_871884588982__INCLUDED_)
