#if !defined(AFX_DLGSETTINGRECEIPTFORMAT_H__7475B47F_7E5E_4CC6_9B63_29E3305D82DA__INCLUDED_)
#define AFX_DLGSETTINGRECEIPTFORMAT_H__7475B47F_7E5E_4CC6_9B63_29E3305D82DA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// dlgsettingreceiptformat.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgSettingReceiptFormat dialog

class CDlgSettingReceiptFormat : public CDialog
{
// Construction
public:
	CDlgSettingReceiptFormat(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgSettingReceiptFormat)
	enum { IDD = IDD_SETTING_RECEIPT_FORMAT };
	CListCtrl	m_list;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgSettingReceiptFormat)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgSettingReceiptFormat)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void Show();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSETTINGRECEIPTFORMAT_H__7475B47F_7E5E_4CC6_9B63_29E3305D82DA__INCLUDED_)
