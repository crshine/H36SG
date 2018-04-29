#if !defined(AFX_DLGCREATECARD1_H__C5D34A98_1934_403F_B082_E33EB762DD30__INCLUDED_)
#define AFX_DLGCREATECARD1_H__C5D34A98_1934_403F_B082_E33EB762DD30__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// dlgcreatecard1.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgCreateCard1 dialog

class CDlgCreateCard1 : public CDialog
{
// Construction
public:
	bool CheckInput();
	CDlgCreateCard1();
	~CDlgCreateCard1();

// Dialog Data
	//{{AFX_DATA(CDlgCreateCard1)
	enum { IDD = IDD_CARD_CREATE1 };
	CString	m_TypeBrief;
	CString	m_NumberPart;
	USHORT m_TypeId;
	int		m_nTypePart;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CDlgCreateCard1)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CDlgCreateCard1)
	virtual BOOL OnInitDialog();
	afx_msg void OnCate1();
	afx_msg void OnCate2();
	afx_msg void OnCate3();
	afx_msg void OnCate4();
	afx_msg void OnAutoGainNo();
	afx_msg void OnQuery();
	virtual void OnOK(){};
	virtual void OnCancel(){};
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnSelchangeCardTypePart();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	LPVOID m_pDlg;
	void UpdateBrief();
	enum Direction {dir_Obj2Dlg, dir_Dlg2Obj};
	void PassValue(Direction);	//对象与对话框之间值的传递
	void InitControl();
public: 
	void SetParentDlg(LPVOID pDlg){m_pDlg = pDlg;}
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCREATECARD1_H__C5D34A98_1934_403F_B082_E33EB762DD30__INCLUDED_)
