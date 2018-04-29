#if !defined(AFX_DLGCREATECARD3_H__87C3A171_7340_446C_BA20_5EC8541E786F__INCLUDED_)
#define AFX_DLGCREATECARD3_H__87C3A171_7340_446C_BA20_5EC8541E786F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// dlgcreatecard3.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgCreateCard3 dialog

class CDlgCreateCard3 : public CDialog
{
	DECLARE_DYNCREATE(CDlgCreateCard3)

// Construction
public:
	bool CheckInput();
	CDlgCreateCard3();
	~CDlgCreateCard3();

// Dialog Data
	//{{AFX_DATA(CDlgCreateCard3)
	enum { IDD = IDD_CARD_CREATE3 };
	CString	m_addr1;
	CString	m_addr2;
	CString	m_addr3;
	CString	m_ic;
	CString	m_id;
	CString	m_name;
	CString	m_plate;
	CString	m_tel;
	CString	m_zip;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CDlgCreateCard3)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CDlgCreateCard3)
	afx_msg void OnNewHolder();
	afx_msg void OnNoHolder();
	afx_msg void OnExistHolder();
	virtual BOOL OnInitDialog();
	virtual void OnOK(){};
	virtual void OnCancel(){};
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	void InitControl();
	enum Direction {dir_Obj2Dlg, dir_Dlg2Obj};
	void PassValue(Direction);	//对象与对话框之间值的传递
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCREATECARD3_H__87C3A171_7340_446C_BA20_5EC8541E786F__INCLUDED_)
